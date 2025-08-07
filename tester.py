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

def print_panels(input_content, interleaved_output, expected_content):
    """Print input, output (interleaved stdout/stderr), and expected output in horizontal panels.
    OUTPUT panel: stdout in bold cyan, stderr in regular cyan (not bold), both in true emission order.
    """
    panels = []
    colors = []

    if input_content.strip():
        panels.append(("INPUT", input_content.strip()))
        colors.append("\033[94m")  # Blue

    # Compose OUTPUT panel: interleaved stdout/stderr
    output_panel_lines = []
    cyan = "\033[96m"
    bold = "\033[1m"
    reset = "\033[0m"
    if interleaved_output:
        for is_stdout, line in interleaved_output:
            padded_line = "  " + line
            if is_stdout:
                output_panel_lines.append(f"{cyan}{bold}{padded_line}{reset}")
            else:
                output_panel_lines.append(f"{cyan}{padded_line}{reset}")
    if output_panel_lines:
        panels.append(("OUTPUT", "\n".join(output_panel_lines)))
        colors.append(cyan)

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
            # Remove color codes for length calculation
            line_no_esc = line.replace("\033[96m", "").replace("\033[1m", "").replace("\033[0m", "")
            if len(line_no_esc) > panel_width - 4:
                # Truncate, preserve color codes at start
                prefix = ""
                if line.startswith("\033[96m\033[1m"):
                    prefix = "\033[96m\033[1m"
                    suffix = "\033[0m"
                elif line.startswith("\033[96m"):
                    prefix = "\033[96m"
                    suffix = "\033[0m"
                else:
                    prefix = color
                    suffix = reset
                formatted_lines.append(f"{prefix}  {line_no_esc[:panel_width-6] + '...'}{suffix}")
            else:
                formatted_lines.append(line if line.startswith("\033") else f"{color}  {line}{reset}")
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
            content_no_color = content.replace(color, "").replace("\033[1m", "").replace(reset, "")
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

    # Only compare output_content (stdout) to expected_content for match
    # Reconstruct stdout from interleaved_output for comparison
    reconstructed_stdout = "\n".join(line for is_stdout, line in interleaved_output if is_stdout)
    return expected_content.strip() == reconstructed_stdout.strip() if expected_content else True

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
    import pty
    import select

    process = None
    start_time = time.monotonic()
    interleaved_output = []  # List of (is_stdout, line)

    # Marker for stderr lines
    STDERR_MARKER = "01987257-34a8-74b1-b7eb-0da7dce117e5"

    # Open input file for reading
    input_f = open("user/input.txt", "rb")

    # Create a pty
    master_fd, slave_fd = pty.openpty()

    try:
        # Start the subprocess, redirecting both stdout and stderr to the slave end of the pty
        process = subprocess.Popen(
            command,
            stdin=input_f,
            stdout=slave_fd,
            stderr=slave_fd,
            close_fds=True
        )
        p = psutil.Process(process.pid)

        os.close(slave_fd)  # Only parent reads from master

        # Read from the pty master, line by line, as bytes
        buffer = b""
        while True:
            # Monitor memory usage
            try:
                current_memory_rss = p.memory_info().rss
                if current_memory_rss > peak_memory_rss:
                    peak_memory_rss = current_memory_rss
            except (psutil.NoSuchProcess, psutil.AccessDenied):
                pass

            rlist, _, _ = select.select([master_fd], [], [], 0.01)
            if master_fd in rlist:
                try:
                    data = os.read(master_fd, 1024)
                except OSError:
                    break
                if not data:
                    break
                buffer += data
                while b"\n" in buffer:
                    line, buffer = buffer.split(b"\n", 1)
                    try:
                        decoded = line.decode("utf-8", errors="replace")
                    except Exception:
                        decoded = line.decode("utf-8", errors="ignore")
                    # Strip trailing \r and whitespace before checking for marker
                    decoded_stripped = decoded.rstrip('\r\n')
                    if decoded_stripped.endswith(STDERR_MARKER):
                        # Remove marker and any trailing whitespace before coloring
                        stripped = decoded_stripped[: -len(STDERR_MARKER)].rstrip()
                        interleaved_output.append((False, stripped))
                    else:
                        interleaved_output.append((True, decoded_stripped))
            if process.poll() is not None and not rlist:
                # Drain any remaining data
                if buffer:
                    try:
                        decoded = buffer.decode("utf-8", errors="replace")
                    except Exception:
                        decoded = buffer.decode("utf-8", errors="ignore")
                    decoded_stripped = decoded.rstrip('\r\n')
                    if decoded_stripped.endswith(STDERR_MARKER):
                        stripped = decoded_stripped[: -len(STDERR_MARKER)].rstrip()
                        interleaved_output.append((False, stripped))
                    else:
                        interleaved_output.append((True, decoded_stripped))
                break

    finally:
        if input_f:
            input_f.close()
        os.close(master_fd)

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
    output_matches = print_panels(input_content, interleaved_output, expected_output)

    print(f"time -> {duration:.3f}s, mem -> {format_bytes(peak_memory_rss)}")

    # Exit with non-zero code if output doesn't match expected
    if expected_output and not output_matches:
        sys.exit(1)


if __name__ == "__main__":
    main()
