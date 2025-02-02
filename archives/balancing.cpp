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
    // USACO 2016 February Contest, Silver
    // Problem 2. Load Balancing
    // https://usaco.org/index.php?page=viewproblem2&cpid=619
    setIO("balancing", false);
    int numCows = nxt();
    // int _ = nxt();  <- add to handle the bronze version
    vector<pair<int, int>> cowPositions(numCows);
    for (auto& pos: cowPositions) {
        pos = make_pair(nxt(), nxt());
    }
    set<int> potentialVerticalFences = {};
    set<int> potentialHorizontalFences = {};
    for (auto pos: cowPositions) {
        potentialVerticalFences.insert(pos.first+1);
        potentialHorizontalFences.insert(pos.second+1);
    }
    int minMaxRegionSize = 1000;
    for (auto verticalFence: potentialVerticalFences) {
        for (auto horizontalFence: potentialHorizontalFences) {
            int topRight = 0, bottomRight = 0, bottomLeft = 0, topLeft = 0;
            for (auto pos: cowPositions) {
                if (pos.first > verticalFence && pos.second > horizontalFence) topRight++;
                if (pos.first > verticalFence && pos.second < horizontalFence) bottomRight++;
                if (pos.first < verticalFence && pos.second < horizontalFence) bottomLeft++;
                if (pos.first < verticalFence && pos.second > horizontalFence) topLeft++;
            }
            minMaxRegionSize = min(minMaxRegionSize, max(max(topRight, bottomRight), max(bottomLeft, topLeft)));
        }
    }
    cout << minMaxRegionSize << endl;

    return 0;
}
