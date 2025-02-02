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
    // NOT FULLY WORKING
    // D. Rudolph and Christmas Tree
    // https://codeforces.com/contest/1846/problem/D
    setIO("", false);
    int numTestCases = nxt();
    for (int currentCase = 0; currentCase < numTestCases; currentCase++) {
        long long numBranches = nxt(), triangleBase = nxt(), triangleHeight = nxt();
        vi branchPositions(numBranches);
        for (auto& position: branchPositions) position = nxt();
        int currentCutoff = branchPositions.back() + triangleHeight + 1;
        reverse(all(branchPositions));

        vector<double> triangleAreas(triangleHeight + 1);
        triangleAreas[0] = 0;

        double triangleSlope = static_cast<double>(
            static_cast<float>(triangleBase)/static_cast<float>(triangleHeight)
        );
        for (int height = 1; height <= triangleHeight; height++) {
            double areaAtHeight = static_cast<double>(height) * triangleSlope;
            areaAtHeight *= static_cast<double>(height);
            triangleAreas[height] = areaAtHeight;
        }
        for (auto area: triangleAreas) {
            cout << area << " ";
        }
        cout << endl;
        double totalArea = 0;
        double defaultArea = 0.5 * static_cast<double>(triangleBase) * static_cast<double>(triangleHeight);

        for (int branchPos: branchPositions) {
            int topSection = branchPos + triangleHeight - currentCutoff;
            if (topSection > 0) {
                cout << topSection << "|" << triangleAreas[triangleHeight-topSection+1] << endl;
                totalArea += triangleAreas[topSection];
            } else {
                totalArea += defaultArea;
            }
            currentCutoff = branchPos;
        }
        printf("%f\n", totalArea);
    }
    return 0;
}
