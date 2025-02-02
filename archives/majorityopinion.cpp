#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
using namespace std;
int nxt() {int a; cin >> a; return a;};

int main() {
    // USACO 2024 January Contest, Bronze
    // Problem 1. Majority Opinion
    // https://usaco.org/index.php?page=viewproblem2&cpid=1371
    int numTestCases = nxt();
    for (int testCase = 0; testCase < numTestCases; testCase++) {
        int numCows = nxt();
        vi preferences(numCows);
        for (auto& pref: preferences) pref = nxt();
        set<int> majorityHayTypes = {};

        int currentHayType = -1;
        int consecutiveCount = 0;

        for (auto iter = preferences.begin(); iter < preferences.end(); iter++) {
            // Check for same hay type with gap of 1
            if (*iter == *(iter+2)) {
                majorityHayTypes.insert(*iter);
            }

            // Check for consecutive hay types
            if (currentHayType == *iter) {
                consecutiveCount++;
            } else {
                if (consecutiveCount >= 2) {
                    majorityHayTypes.insert(currentHayType);
                }
                currentHayType = *iter;
                consecutiveCount = 1;
            }
        }

        if (consecutiveCount >= 2) {
            majorityHayTypes.insert(currentHayType);
        }

        if (majorityHayTypes.empty()) {
            cout << -1 << endl;
        } else {
            vi result(all(majorityHayTypes));
            for (int i = 0; i < result.size()-1; i++) {
                cout << result[i] << " ";
            }
            cout << result.back() << endl;
        }
    }
    return 0;
}
