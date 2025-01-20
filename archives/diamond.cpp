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
    // USACO 2016 US Open Contest, Bronze
    // Problem 1. Diamond Collector
    // https://usaco.org/index.php?page=viewproblem2&cpid=639
    setIO("diamond", false);
    int n = nxt(); int k = nxt();
    vi ns(n); for (auto& i: ns) { i = nxt(); };
    int best = -1;
    int mi = *min_element(all(ns));
    int ma = *max_element(all(ns));
    for (int v = mi; v < ma; v++) {
        // window from v ..= v + k (inclusive both sides)
        int t = 0;
        for (auto p: ns) {
            if (p >= v && p <= v+k) t++;
        }
        best = max(t, best);
    }
    cout << best << endl;
    return 0;
}
