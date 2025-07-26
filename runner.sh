clear && clang++ main.cpp -DAADISHV -std=c++17 -Wall -Wextra -O2 -lm \
    && uv run test.py --input input.txt ./a.out
# with debug symbols:
# clear && clang++ main.cpp -DAADISHV -std=c++17 -Wall -Wextra -g -O0 -lm && time ./a.out < input.txt
