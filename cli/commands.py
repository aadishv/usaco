import sys
from rich.console import Console

from .problem_manager import ProblemManager
from .display import show_usage

console = Console()

def main():
    """Main CLI entry point"""
    if len(sys.argv) < 2:
        show_usage()
        sys.exit(1)

    # Parse flags
    args = sys.argv[1:]
    open_browser = False

    if "-o" in args:
        open_browser = True
        args.remove("-o")

    if not args:
        show_usage()
        sys.exit(1)

    command = args[0]
    manager = ProblemManager()

    if command == "run":
        if len(args) < 2:
            show_usage()
            sys.exit(1)

        target = args[1]
        if target == "random":
            manager.open_random_problem(open_browser=open_browser)
        else:
            manager.open_specific_problem(target, open_browser=open_browser)
            

    elif command == "list":
        manager.list_current_problem()

    else:
        show_usage()
        sys.exit(1)