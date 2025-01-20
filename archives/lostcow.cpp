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

int main() {
    // USACO 2017 US Open Contest, Bronze
    // Problem 1. The Lost Cow
    // https://usaco.org/index.php?page=viewproblem2&cpid=735
    setIO("lostcow", false);
    int startPosition, targetPosition;
    cin >> startPosition >> targetPosition;
    int currentPosition = startPosition;
    int moveDistance = 1;
    int totalSteps = 0;
    while (currentPosition != targetPosition) {
        totalSteps++;
        if (moveDistance < 0) currentPosition--;
        else currentPosition++;
        if (currentPosition == startPosition + moveDistance) moveDistance *= -2;
        cerr << moveDistance << '|' << endl;
    }
    cout << totalSteps << endl;
    return 0;
}
