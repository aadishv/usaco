// echo "clear && clang++ main.cpp -std=c++17 -Wall -Wextra -O2 -lm && time ./a.out < input.txt" > ~/.runner_settings
// cp template.cpp main.cpp
#include <bits/stdc++.h>

#define vi vector<int>
#define all(a) a.begin(), a.end()

using namespace std;

void setIO(string name = "", bool maxio = false) {
    if (name.size() > 0){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
    if (maxio) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
}
int nxt() { int a; cin >> a; return a; }

int main() {
    // USACO 2018 January Contest, Bronze
    // Problem 1. Blocked Billboard II
    // https://usaco.org/index.php?page=viewproblem2&cpid=783
    setIO("billboard", false);
    int billboard_x1 = nxt(), billboard_y1 = nxt(), billboard_x2 = nxt(), billboard_y2 = nxt();
    int blocking_x1 = nxt(), blocking_y1 = nxt(), blocking_x2 = nxt(), blocking_y2 = nxt();
    int max_x = -1001, min_x = 1001, max_y = -1001, min_y = 1001;
    for (auto x = billboard_x1; x < billboard_x2; x++) {
        for (auto y = billboard_y1; y < billboard_y2; y++) {
            if (!(x >= blocking_x1 && x < blocking_x2 && y >= blocking_y1 && y < blocking_y2)) {
                max_x = std::max(max_x, x); min_x = min(min_x, x);
                max_y = std::max(max_y, y); min_y = min(min_y, y);
            }
        }
    }
    if (max_x == -1001 || min_x == 1001 || max_y == -1001 || min_y == 1001) { cout << 0 << endl; return 0; }
    cout << (max_x-min_x+1)*(max_y-min_y+1) << endl;
    return 0;
}
