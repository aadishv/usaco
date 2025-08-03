clear \
&& clang++ user/main.cpp -DAADISHV -std=c++17 \
    -Wall -Wextra -O2 -lm -Wno-unused-parameter \
&& uv run tester.py
# with debug symbols:
# clear && clang++ main.cpp -DAADISHV -std=c++17 -Wall -Wextra -g -O0 -lm && time ./a.out < input.txt
