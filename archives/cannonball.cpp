#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
using namespace std;
int nxt() {int a; cin >> a; return a;};
struct Obstacle {
    bool typ;
    int v;
    bool broken = false;
};
void dbg(vi vs, string id = "") {
    if (id != "") {
        cout << id << "\t";
    }
    for (auto v: vs) cout << v << " ";
    cout << endl;
}
int main() {
    // USACO 2024 January Contest, Bronze
    // Problem 2. Cannonball
    // https://usaco.org/index.php?page=viewproblem2&cpid=1372
    const bool JUMP_PAD = false, TARGET_BLOCK = true;
    int numPositions = nxt();
    int currentPosition = nxt() - 1;
    int currentPower = 1;
    int currentDirection = 1;

    vector<Obstacle> obstacles;
    for (int i = 0; i < numPositions; i++) {
        obstacles.push_back({ nxt() > 0, nxt() });
    }

    // Track visited states to detect cycles
    set<tuple<int, int, int>> visitedStates;  // (position, power, direction)
    const int MAX_ITERATIONS = 20000;  // 2*100*100*10
    int iterations = 0;

    // Simulate cannonball movement
    while (0 <= currentPosition && currentPosition <= numPositions && iterations < MAX_ITERATIONS) {
        auto currentState = make_tuple(currentPosition, currentPower, currentDirection);
        if (visitedStates.count(currentState)) break;
        visitedStates.insert(currentState);

        auto& obstacle = obstacles[currentPosition];

        if (obstacle.typ == JUMP_PAD) {
            currentPower += obstacle.v;
            currentDirection *= -1;
        } else if (obstacle.typ == TARGET_BLOCK) {
            if (currentPower >= obstacle.v) {
                obstacle.broken = true;
            }
        }
        currentPosition += currentPower * currentDirection;
        iterations++;
    }

    // Count broken targets
    int brokenTargets = 0;
    for (const auto& obstacle : obstacles) {
        brokenTargets += obstacle.broken;
    }
    cout << brokenTargets << endl;
    return 0;
}
