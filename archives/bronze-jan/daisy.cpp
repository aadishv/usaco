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
    // USACO 2020 December Contest, Bronze
    // Problem 2. Daisy Chains
    // https://usaco.org/index.php?page=viewproblem2&cpid=1060
    setIO("", false);
    int nflowers = nxt();
    vi petals(nflowers); for (auto& p: petals) p = nxt();
    int t = nflowers; // every photo of a single flower
    for (int i = 0; i < nflowers-1; i++) {
        for (int j = i+1; j < nflowers; j++) {
            // capture all between i...j
            int avg = 0;
            for (int a = i; a <= j; a++) avg += petals[a];
            if (avg % (j-i+1) != 0) continue;
            avg /= j-i+1;
            // bool g = false;
            for (int a = i; a <= j; a++) {
                if (petals[a] == avg) { t++; break; }
            }
            // cout << i << j << avg << endl;
        }
    }
    cout << t << endl;
    return 0;
}
