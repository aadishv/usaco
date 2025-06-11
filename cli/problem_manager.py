import json
import random
import webbrowser
import sys
from pathlib import Path
import re
import urllib.request
import time
import zipfile

from .display import display_problem_card, print_success, print_error, print_warning, print_info

class ProblemManager:
    """Manages USACO problem operations"""
    
    def __init__(self):
        self.base_dir = Path(__file__).parent.parent
        self.problems_json = self.base_dir / "problems.json"
        self.temp_dir = self.base_dir / "tmp"
        self.temp_dir.mkdir(exist_ok=True)
        
    def load_problems(self):
        """Load problems from problems.json"""
        try:
            with open(self.problems_json, "r", encoding="utf-8") as f:
                problems_dict = json.load(f)
            return list(problems_dict.values())
        except Exception as e:
            print_error(f"Failed to load problems: {e}")
            sys.exit(1)
    
    def filter_eligible_problems(self, problems):
        """Filter problems to only include 2015+ or December 2014"""
        filtered = []
        for problem in problems:
            source = problem.get("source", {})
            year = source.get("year", 0)
            contest = str(source.get("contest", "")).lower()
            
            if year and (int(year) > 2014 or (int(year) == 2014 and contest == "december")):\
                filtered.append(problem)
        
        return filtered
    
    def open_random_problem(self, open_browser=False):
        """Open a random eligible problem"""
        problems = self.load_problems()
        filtered = self.filter_eligible_problems(problems)
        
        if not filtered:
            print_error("No eligible problems found.")
            sys.exit(1)
            
        problem = random.choice(filtered)
        url = problem.get("url")
        
        if not url:
            print_error("Problem has no URL.")
            sys.exit(1)
        
        display_problem_card(problem)
        
        if open_browser:
            webbrowser.open(url)

        try:
            self.download_test_data(problem)
        except Exception as e:
            print_warning(f"Could not download test data: {e}")
    
    def open_specific_problem(self, url, open_browser=False):
        """Open a specific problem by URL"""
        problems = self.load_problems()
        filtered = self.filter_eligible_problems(problems)
        
        for problem in filtered:
            if problem.get("url") == url:
                display_problem_card(problem)

                if open_browser:
                    webbrowser.open(url)

                try:
                    self.download_test_data(problem)
                except Exception as e:
                    print_warning(f"Could not download test data: {e}")
                return
        
        print_error("Problem not found or not eligible (must be 2015 or later, or December 2014).")
        sys.exit(1)

    def list_current_problem(self):
        """Show the card for the current problem from problem.json"""
        problem_json_path = self.temp_dir / "problem.json"
        
        if not problem_json_path.exists():
            print_error("No current problem found. Run \'usaco run random\' or \'usaco run <url>\' first.")
            sys.exit(1)
        
        try:
            with open(problem_json_path, 'r') as f:
                problem_info = json.load(f)
                
            cpid = problem_info.get("cpid")
            if not cpid:
                print_error("Invalid problem.json file.")
                sys.exit(1)
            
            # Find the problem in problems.json by cpid
            problems = self.load_problems()
            for problem in problems:
                if problem.get("id") == cpid:
                    test_cases = problem_info.get("cases", "Unknown")
                    display_problem_card(problem, test_cases)
                    return
            
            print_error(f"Problem with CPID {cpid} not found in problems.json.")
            sys.exit(1)
        
        except Exception as e:
            print_error(f"Error reading problem.json: {e}")
            sys.exit(1)

    def download_test_data(self, problem):
        """Download and extract test data for a problem"""
        source = problem.get("source", {})
        year = str(source.get("year", ""))
        contest = str(source.get("contest", "")).lower()
        division = str(source.get("division", "")).lower()
        title = problem.get("title", {})
        place = title.get("place", None)
        cpid = problem.get("id", None)

        if not (year and contest and division and place and cpid):
            print_warning("Not enough info to find test data zip.")
            return

        # Map contest to results page suffix
        contest_map = {
            "us open": "open",
            "open": "open",
            "december": "dec",
            "january": "jan",
            "february": "feb",
            "march": "mar"
        }
        contest_suffix = contest_map.get(contest, contest)
        yy = year[-2:]

        # Construct the results page URL
        results_url = f"https://usaco.org/index.php?page={contest_suffix}{yy}results"
        print_info(f"Fetching contest page: {results_url}")

        # Fetch the results page with retry
        html = self._fetch_with_retry(results_url)
        if not html:
            return

        # Find the test data zip link
        zip_url = self._extract_zip_url(html, cpid)
        if not zip_url:
            return
        
        # Download and extract the zip
        self._download_and_extract_zip(zip_url, cpid)

    def _fetch_with_retry(self, url, max_attempts=3):
        """Fetch URL with retry logic"""
        for attempt in range(max_attempts):
            try:
                with urllib.request.urlopen(url) as resp:
                    return resp.read().decode("utf-8")
            except Exception as e:
                print_warning(f"Attempt {attempt + 1} failed to fetch page: {e}")
                if attempt < max_attempts - 1:
                    time.sleep(1)
                else:
                    print_error("Failed to fetch page after 3 attempts.")
                    return None

    def _extract_zip_url(self, html, cpid):
        """Extract zip URL from HTML"""
        # Pattern to match: cpid=XXX'>View problem</a>&nbsp | &nbsp <a href='path.zip'>Test data</a>
        pattern = rf"cpid={cpid}'>View problem</a>&nbsp \| &nbsp <a href='([^']+\.zip)'>Test data</a>"
        match = re.search(pattern, html, re.DOTALL)
        
        if not match:
            print_warning(f"No test data zip found for problem {cpid}.")
            return None

        zip_path = match.group(1)
        if not zip_path.startswith("http"):
            return "https://usaco.org/" + zip_path.lstrip("/")
        return zip_path

    def _download_and_extract_zip(self, zip_url, cpid):
        """Download and extract zip file"""
        zip_name = zip_url.split("/")[-1]
        print_info(f"Downloading test data: {zip_name}")

        # Download to temp directory
        temp_zip_path = self.temp_dir / zip_name

        # Download with retry
        if not self._download_file_with_retry(zip_url, temp_zip_path):
            return

        # Create CPID directory and extract
        cpid_dir = self.temp_dir / str(cpid)
        cpid_dir.mkdir(exist_ok=True)

        try:
            with zipfile.ZipFile(temp_zip_path, 'r') as zip_ref:
                zip_ref.extractall(cpid_dir)
            print_success(f"Extracted test data to {cpid_dir}")

            # Count test cases and create problem.json
            self._create_problem_json(cpid, cpid_dir)

            # Clean up zip file
            temp_zip_path.unlink()
            print_success("Cleaned up temporary files")

        except Exception as e:
            print_error(f"Failed to extract zip file: {e}")
            # Clean up zip file even if extraction failed
            if temp_zip_path.exists():
                temp_zip_path.unlink()

    def _download_file_with_retry(self, url, path, max_attempts=3):
        """Download file with retry logic"""
        for attempt in range(max_attempts):
            try:
                urllib.request.urlretrieve(url, path)
                print_success("Downloaded test data")
                return True
            except Exception as e:
                print_warning(f"Attempt {attempt + 1} failed to download: {e}")
                if attempt < max_attempts - 1:
                    time.sleep(1)
                else:
                    print_error("Failed to download zip file after 3 attempts.")
                    return False

    def _create_problem_json(self, cpid, cpid_dir):
        """Create problem.json with metadata"""
        unzipped_files = list(cpid_dir.glob("*"))
        num_files = len([f for f in unzipped_files if f.is_file()])
        cases = num_files // 2  # Assuming pairs of input/output files

        problem_info = {
            "cpid": cpid,
            "cases": cases
        }

        problem_json_path = self.temp_dir / "problem.json"
        with open(problem_json_path, 'w') as f:
            json.dump(problem_info, f, indent=2)
        
        print_success(f"Created problem.json with {cases} test cases")