#!/usr/bin/env python3

import sys
from pathlib import Path
# Add the current directory to Python path for local imports
sys.path.insert(0, str(Path(__file__).parent))

from cli.commands import main

if __name__ == "__main__":
    main()