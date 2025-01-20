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
    // USACO 2016 January Contest, Bronze
    // Problem 3. Mowing the Field
    // https://usaco.org/index.php?page=viewproblem2&cpid=593
    setIO("mowing", false);
    int numSteps = nxt();

    pair<int, int> currentPosition = make_pair(0,0);
    map<pair<int, int>, int> mowedPositions = {{make_pair(0,0), 0}};
    int currentTime = 0;
    int minRegrowthTime = 1001;

    for (int step = 0; step < numSteps; step++) {
        char direction; cin >> direction;
        pair<int, int> movement;
        {
            if (direction == 'N') movement = make_pair(0, 1);
            if (direction == 'S') movement = make_pair(0, -1);
            if (direction == 'E') movement = make_pair(-1, 0);
            if (direction == 'W') movement = make_pair(1, 0);
        }
        int stepsInDirection = nxt();
        for (int step = 0; step < stepsInDirection; step++) {
            currentTime++;
            currentPosition.first += movement.first;
            currentPosition.second += movement.second;
            if (mowedPositions.count(currentPosition)) {
                minRegrowthTime = min(minRegrowthTime, currentTime - mowedPositions[currentPosition]);
            }
            mowedPositions[currentPosition] = currentTime;
        }
    }
    if (minRegrowthTime == 1001) minRegrowthTime = -1;
    cout << minRegrowthTime << endl;
    return 0;
}
