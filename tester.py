#!/usr/bin/env python
# /// script
# requires-python = ">=3.8"
# dependencies = [
#   "psutil",
# ]
# ///

"""
A script to run ./a.out with input.txt, measure its execution time, track its peak
memory usage (RSS), and compare output with output.txt if it exists.
"""

import sys
import subprocess
import time
import psutil
import os

def format_bytes(byte_count):
    """Converts a byte count into a human-readable string (KB, MB, GB)."""
    if byte_count is None:
        return "N/A"
    power = 1024
    n = 0
    power_labels = {0: '', 1: 'K', 2: 'M', 3: 'G', 4: 'T'}
    while byte_count >= power and n < len(power_labels):
        byte_count /= power
        n += 1
    return f"{byte_count:.2f} {power_labels[n]}B"

def print_panels(input_content, output_content, expected_content):
    """Print input, output, and expected output in three horizontal panels."""
    panels = []
    colors = []

    if input_content.strip():
        panels.append(("INPUT", input_content.strip()))
        colors.append("\033[94m")  # Blue
    if output_content.strip():
        panels.append(("OUTPUT", output_content.strip()))
        colors.append("\033[96m")  # Cyan
    if expected_content and expected_content.strip():
        panels.append(("EXPECTED", expected_content.strip()))
        colors.append("\033[93m")  # Yellow

    if not panels:
        return

    # Calculate panel width (account for borders)
    terminal_width = os.get_terminal_size().columns if hasattr(os, 'get_terminal_size') else 120
    border_space = len(panels) + 1  # Account for vertical borders
    panel_width = max(30, (terminal_width - border_space) // len(panels) - 1)

    # Split content into lines and pad panels to same height
    panel_lines = []
    max_height = 0

    for i, (title, content) in enumerate(panels):
        lines = content.split('\n')
        color = colors[i]
        reset = "\033[0m"

        # Truncate long lines and add header
        header = f"- {title} " + "─" * (panel_width - len(title) - 3)
        formatted_lines = [f"{color}{header}{reset}"]

        for line in lines:
            if len(line) > panel_width - 4:
                formatted_lines.append(f"{color}  {line[:panel_width-6] + '...'}{reset}")
            else:
                formatted_lines.append(f"{color}  {line}{reset}")
        panel_lines.append(formatted_lines)
        max_height = max(max_height, len(formatted_lines))

    # Pad all panels to same height
    for i, lines in enumerate(panel_lines):
        color = colors[i]
        reset = "\033[0m"
        while len(lines) < max_height:
            lines.append(f"{color} {reset}")

    # Print panels side by side with borders
    for i in range(max_height):
        row_parts = []
        for j, lines in enumerate(panel_lines):
            color = colors[j]
            reset = "\033[0m"
            content = lines[i] if i < len(lines) else f"{color}{reset}"

            # Calculate actual content length (without color codes)
            content_no_color = content.replace(color, "").replace(reset, "")
            padding_needed = panel_width - len(content_no_color)
            padded_content = content + " " * padding_needed

            # Add colored border
            row_parts.append(f"{color}│{reset}{padded_content}")

        # Add final right border
        final_color = colors[-1] if colors else ""
        print("".join(row_parts) + f"{final_color}│{reset}")

    # Print bottom border
    bottom_parts = []
    for j, _ in enumerate(panel_lines):
        color = colors[j]
        reset = "\033[0m"
        bottom_border = "─" * panel_width
        bottom_parts.append(f"{color}└{bottom_border}{reset}")

    final_color = colors[-1] if colors else ""
    print("".join(bottom_parts) + f"{final_color}┘{reset}")

    return expected_content == output_content if expected_content else True

def main():
    """Main function to execute and monitor the command."""
    # Hardcoded values from runner.sh
    input_file = "user/input.txt"
    command = ["./a.out"]

    # Check if input file exists
    if not os.path.exists(input_file):
        print(f"Error: Input file not found: '{input_file}'")
        sys.exit(1)

    # Check if executable exists
    if not os.path.exists(command[0]):
        print(f"Error: Executable not found: '{command[0]}'")
        sys.exit(1)

    input_f = None
    try:
        input_f = open(input_file, 'r')
    except FileNotFoundError:
        print(f"Error: Input file not found: '{input_file}'")
        sys.exit(1)

    peak_memory_rss = 0
    process = None
    start_time = time.monotonic()
    program_output = ""

    try:
        # Start the subprocess, capturing stdout and passing input file to stdin
        process = subprocess.Popen(
            command,
            stdin=input_f,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        p = psutil.Process(process.pid)

        # Monitor the process in a loop
        while process.poll() is None:
            try:
                # Get Resident Set Size (RSS) memory
                current_memory_rss = p.memory_info().rss
                if current_memory_rss > peak_memory_rss:
                    peak_memory_rss = current_memory_rss
            except (psutil.NoSuchProcess, psutil.AccessDenied):
                # Process might have finished between poll() and memory_info()
                break
            # Sleep for a short interval to avoid busy-waiting
            time.sleep(0.01)

        # Get the output
        stdout, stderr = process.communicate()
        program_output = stdout

    except FileNotFoundError:
        print(f"Error: Command not found: '{command[0]}'")
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)
    finally:
        # Ensure the input file is cleaned up
        if input_f:
            input_f.close()

    end_time = time.monotonic()
    duration = end_time - start_time

    # Final check in case the process was too fast to capture memory
    try:
        if p.is_running():
             final_memory_rss = p.memory_info().rss
             if final_memory_rss > peak_memory_rss:
                peak_memory_rss = final_memory_rss
    except (psutil.NoSuchProcess, psutil.AccessDenied):
        pass # Process is already gone

    # Read input and expected output
    input_content = ""
    expected_output = ""

    try:
        with open(input_file, 'r') as f:
            input_content = f.read()
    except Exception:
        pass

    if os.path.exists("user/output.txt"):
        try:
            with open("user/output.txt", 'r') as f:
                expected_output = f.read()
        except Exception:
            pass

    # Show panels
    output_matches = print_panels(input_content, program_output, expected_output)

    print(f"time -> {duration:.3f}s, mem -> {format_bytes(peak_memory_rss)}")

    # Exit with non-zero code if output doesn't match expected
    if expected_output and not output_matches:
        sys.exit(1)


if __name__ == "__main__":
    main()
