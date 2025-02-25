#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

vector<int> getNeighbors(int position) {
    vector<int> gridMoves = {-1, 1, 10, -10};
    vector<int> validNeighbors = {};
    for (int move : gridMoves) {
        int neighborPos = move + position;
        if (neighborPos < 100 && neighborPos > 0) {
            validNeighbors.push_back(neighborPos);
        }
    }
    return validNeighbors;
}

int calculateManhattanDistance(int pos1, int pos2) {
    return abs((pos1 % 10) - (pos2 % 10)) + abs(int(pos1 / 10) - int(pos2 / 10));
}

int main() {
    // USACO 2019 US Open Contest, Bronze
    // Problem 1. Bucket Brigade
    // https://usaco.org/index.php?page=viewproblem2&cpid=939
    setIO("buckets");
    char currentChar;
    int currentPosition = 0;
    int offsets[4] {-1, 1, 10, -1};
    int barnPosition;
    int rockPosition;
    int lakePosition;

    for (int i = 0; i < 100; i++) {
        cin >> currentChar;
        if (currentChar == 'L') {
            lakePosition = currentPosition;
        }
        else if (currentChar == 'R') {
            rockPosition = currentPosition;
        }
        else if (currentChar == 'B') {
            barnPosition = currentPosition;
        }
        currentPosition++;
    }

    int distance = calculateManhattanDistance(barnPosition, lakePosition);
    bool needsDetour = false;

    if (barnPosition/10 == lakePosition/10 && lakePosition/10 == rockPosition/10) {
        if (((rockPosition > lakePosition) && (rockPosition < barnPosition)) ||
            ((rockPosition < lakePosition) && (rockPosition > barnPosition))) {
            needsDetour = true;
        }
    }

    if (barnPosition%10 == lakePosition%10 && lakePosition%10 == rockPosition%10) {
        if (((rockPosition > lakePosition) && (rockPosition < barnPosition)) ||
            ((rockPosition < lakePosition) && (rockPosition > barnPosition))) {
            needsDetour = true;
        }
    }

    if (needsDetour) {
        distance += 2; // Add extra steps to go around rock when aligned
    }

    cout << distance - 1;
    return 0;
}
