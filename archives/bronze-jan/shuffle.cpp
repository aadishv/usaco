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
int nxt() {
    int a; cin >> a; return a;
}
int idx(vi vec, int v) {
    auto p = vec.begin();
    while (*p != v && p != vec.end()) p++;
    return p - vec.begin();
}
int main() {
    // USACO 2017 December Contest, Bronze
    // Problem 2. The Bovine Shuffle
    // https://usaco.org/index.php?page=viewproblem2&cpid=760
    setIO("shuffle", false);
    int numCows = nxt();
    vector<int> shufflePositions(numCows);
    vector<int> cowOrder(numCows);

    for (auto& position : shufflePositions) position = nxt()-1;
    for (auto& cow : cowOrder) cow = nxt();

    for (int shuffleCount = 0; shuffleCount < 3; shuffleCount++) {
        vector<int> newOrder(numCows);
        int currentPosition = 0;
        for (auto cowId : cowOrder) {
            newOrder[idx(shufflePositions, currentPosition)] = cowId;
            currentPosition++;
        }
        cowOrder = newOrder;
    }

    for (auto cow : cowOrder) {
        cout << cow << endl;
    }
    return 0;
}
