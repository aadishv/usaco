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
bool isValidCowOrder(vi positionedCows, const vi& requiredOrder) {
    auto currentOrderPos = requiredOrder.begin();
    int availableSpaces = 0;
    auto lastFoundOrderPos = requiredOrder.begin();

    for (auto cowId : positionedCows) {
        if (cowId == -1) {
            availableSpaces++;
        }

        // Check if current cow is in required order
        if (find(requiredOrder.begin(), requiredOrder.end(), cowId) != requiredOrder.end()) {
            while (currentOrderPos != requiredOrder.end() && *currentOrderPos != cowId) {
                currentOrderPos++;
            }

            if (currentOrderPos == requiredOrder.end()) {
                return false;
            }

            if (currentOrderPos - lastFoundOrderPos > availableSpaces) {
                return false;
            }

            availableSpaces = 1;
            lastFoundOrderPos = currentOrderPos;
        }
    }
    return true;
}

int main() {
    // USACO 2018 US Open Contest, Bronze
    // Problem 2. Milking Order
    // https://usaco.org/index.php?page=viewproblem2&cpid=832
    setIO("milkorder");
    int totalCows = nxt();
    vi cowPositions(totalCows, -1);
    vi hierarchyOrder(nxt());
    int fixedPositions = nxt();

    // Read hierarchy order
    for (int i = 0; i < hierarchyOrder.size(); i++) {
        hierarchyOrder[i] = nxt();
    }
    cin.ignore();

    // Read fixed positions
    for (int i = 0; i < fixedPositions; i++) {
        int cowId = nxt();
        if (cowId == 1) return 0;
        cowPositions[nxt()-1] = cowId;
        cin.ignore();
    }

    // Try each possible position for cow 1
    for (int pos = 0; pos < cowPositions.size(); pos++) {
        if (cowPositions[pos] == -1) {
            vi testPositions = cowPositions;
            testPositions[pos] = 1;
            if (isValidCowOrder(testPositions, hierarchyOrder)) {
                cout << pos + 1 << endl;
                return 0;
            }
        }
    }
}
