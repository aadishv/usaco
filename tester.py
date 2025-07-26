#!/usr/bin/env python
# /// script
# requires-python = ">=3.8"
# dependencies = [
#   "psutil",
# ]
# ///

"""
A script to run a command, measure its execution time, and track its peak
memory usage (RSS).

Usage:
    uv run main.py [--input <input_file>] <command> [arg1, arg2, ...]

Examples:
    # Run a simple command
    uv run main.py ls -l

    # Compile a C++ program that reads from stdin
    g++ -o my_program my_program.cpp

    # Create an input file
    echo "Hello World" > input.txt

    # Run the program with the input file and monitor it
    uv run main.py --input input.txt ./my_program
"""

import sys
import subprocess
import time
import psutil
import argparse

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

def main():
    """Main function to execute and monitor the command."""
    parser = argparse.ArgumentParser(
        description="Run a command and monitor its execution time and peak memory usage.",
        formatter_class=argparse.RawTextHelpFormatter,
        epilog="""Usage examples:
  # Run a simple command
  uv run main.py ls -l

  # Run a compiled program with an input file
  uv run main.py --input input.txt ./a.out
"""
    )
    parser.add_argument(
        '--input',
        dest='input_file',
        help="Path to a file to be used as stdin for the command."
    )
    parser.add_argument(
        'command',
        nargs='+',
        help="The command to execute and its arguments."
    )

    args = parser.parse_args()
    command = args.command

    input_f = None
    if args.input_file:
        try:
            # Open the input file if specified. This will be passed to stdin.
            input_f = open(args.input_file, 'r')
        except FileNotFoundError:
            print(f"Error: Input file not found: '{args.input_file}'")
            sys.exit(1)

    peak_memory_rss = 0
    process = None
    start_time = time.monotonic()

    try:
        # Start the subprocess, passing the input file handle to stdin
        process = subprocess.Popen(command, stdin=input_f)
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

    except FileNotFoundError:
        print(f"Error: Command not found: '{command[0]}'")
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)
    finally:
        # Ensure the input file and process are cleaned up
        if input_f:
            input_f.close()
        if process and process.poll() is None:
            process.terminate()
            process.wait()

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

    print("\n---")
    print(f"Execution Time: {duration:.3f} seconds")
    print(f"Peak Memory (RSS): {format_bytes(peak_memory_rss)}")


if __name__ == "__main__":
    main()
