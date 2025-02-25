#include <bits/stdc++.h>
#define vi vector<int>
#define ll long long
#define all(i) i.begin(), i.end()
#define cast static_cast
#define DEBUG_MODE true

using namespace std;

template<typename T>
void dbg(vector<T> vs, string id = "") {
    #if DEBUG_MODE
    if (id != "") cerr << id << ":\t";
    for (auto v: vs) cerr << v << " ";
    cerr << endl;
    #else
    return;
    #endif
}
template<typename T>
void dbg(T v, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}

int nxt() {int a; cin >> a; return a;}

void solve_case() {
    int gridSize = nxt();
    int shiftHorizontal = nxt(), shiftVertical = nxt();
    int totalShift = shiftHorizontal + shiftVertical * gridSize;

    // Cell states: 0=empty, 1=possible, 2=invalid, 3=definite
    int cellStates[gridSize * gridSize];
    for (int i = 0; i < gridSize * gridSize; i++) {
        cellStates[i] = 0;
    }

    int totalPieces = 0;
    bool outOfBounds = false;

    // Read grid and process initial states
    for (int row = 0; row < gridSize; row++) {
        string line; cin >> line;
        for (int col = 0; col < gridSize; col++) {
            int currentPos = col + row * gridSize;

            if (line[col] != 'W') {
                cellStates[currentPos]++;
                totalPieces++;
            }

            if (line[col] == 'B') {
                int newCol = col - shiftHorizontal;
                int newRow = row - shiftVertical;
                if (!(0 <= newCol && newCol < gridSize && 0 <= newRow && newRow < gridSize)) {
                    outOfBounds = true;
                }
                cellStates[currentPos - totalShift] += 2;
            }
        }
    }

    if (outOfBounds) {
        cout << -1 << endl;
        return;
    }

    if (totalShift == 0) {
        cout << totalPieces << endl;
        return;
    }

    // Process cell states and check validity
    for (int pos = 0; pos < gridSize * gridSize; pos++) {
        if (cellStates[pos] == 2) {
            cout << -1 << endl;
            return;
        }

        if (cellStates[pos] == 1) {
            int col = pos % gridSize;
            int row = pos / gridSize;
            int newCol = col + shiftHorizontal;
            int newRow = row + shiftVertical;

            if (0 <= newCol && newCol < gridSize && 0 <= newRow && newRow < gridSize) {
                int nextPosition = newRow * gridSize + newCol;
                if (cellStates[nextPosition] == 1) {
                    cellStates[nextPosition] = 0;
                    totalPieces--;
                }
            }
            cellStates[pos] = 3;
        }
    }

    cout << totalPieces << endl;
}
int main() {
    // USACO 2025 January Contest, Bronze
    // Problem 1. Astral Superposition
    // https://usaco.org/index.php?page=viewproblem2&cpid=1467
    int ntestcases = nxt();
    for (int t = 0; t < ntestcases; t++) {
        solve_case();
    }
}
