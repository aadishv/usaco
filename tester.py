#!/usr/bin/env python3
# /// script
# requires-python = ">=3.8"
# dependencies = [
#   "psutil",
# ]
# ///

"""
Execute ./a.out with stdin from user/input.txt.
Measure wall-clock time and peak RSS (bytes). Print:
time_s=<seconds> peak_rss_bytes=<bytes>
"""

import sys
import time
import subprocess

try:
    import psutil
except Exception:
    psutil = None


def _total_rss_bytes(proc: object) -> int:
    if psutil is None:
        return 0
    total = 0
    try:
        with proc.oneshot():
            total += proc.memory_info().rss
            for ch in proc.children(recursive=True):
                try:
                    total += ch.memory_info().rss
                except Exception:
                    pass
    except Exception:
        pass
    return total


def main() -> None:
    # Open input file for stdin
    try:
        input_f = open("user/input.txt", "rb")
    except FileNotFoundError:
        sys.stderr.write("missing input: user/input.txt\n")
        sys.exit(1)

    cmd = ["./a.out", *sys.argv[1:]]
    try:
        p = subprocess.Popen(cmd, stdin=input_f)  # stdout/stderr inherited
    except FileNotFoundError:
        sys.stderr.write("executable not found: ./a.out\n")
        sys.exit(127)

    peak_rss = 0
    proc = None
    if psutil is not None:
        try:
            proc = psutil.Process(p.pid)
        except Exception:
            proc = None

    # Initial sample immediately after spawn
    if proc is not None:
        rss = _total_rss_bytes(proc)
        if rss > peak_rss:
            peak_rss = rss

    start = time.perf_counter()

    # Sample until process exits
    try:
        while True:
            if proc is not None:
                rss = _total_rss_bytes(proc)
                if rss > peak_rss:
                    peak_rss = rss
            if p.poll() is not None:
                break
            time.sleep(0.01)
    finally:
        input_f.close()

    # Final best-effort sample
    if proc is not None:
        rss = _total_rss_bytes(proc)
        if rss > peak_rss:
            peak_rss = rss

    duration = time.perf_counter() - start
    print(f"time_s={duration:.6f} peak_rss_bytes={peak_rss}", flush=True)

    # Propagate child exit code
    sys.exit(p.returncode if p.returncode is not None else 0)


if __name__ == "__main__":
    main()