#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
using namespace std;
int nxt() {int a; cin >> a; return a;};

int main() {
    // USACO 2024 February Contest, Bronze
    // Problem 3. Maximizing Productivity
    // https://usaco.org/index.php?page=viewproblem2&cpid=1397
    int numFarms = nxt(), numQueries = nxt();
    vi closingTimes(numFarms); for (auto& time: closingTimes) time = nxt();
    vi processingTimes(numFarms); for (auto& time: processingTimes) time = nxt();

    vi timeDiffs(numFarms);
    for (int i = 0; i < numFarms; i++) {
       timeDiffs[i] = closingTimes[i] - processingTimes[i];
    }
    sort(all(timeDiffs));

    int maxFeasibleFarms = 0;
    for (int i = 0; i < numFarms; i++) {
        if (processingTimes[i] < closingTimes[i]) {
            maxFeasibleFarms++;
        }
    }

    // Maps desired number of farms to minimum start time needed
    map<int, int> startTimeThresholds;
    for (int numDesired = maxFeasibleFarms; numDesired >= 0; numDesired--) {
        startTimeThresholds[numDesired] = timeDiffs[numFarms - numDesired];
    }

    for (int i = 0; i < numQueries; i++) {
        int farmsWanted = nxt(), startTime = nxt();
        if (startTime < startTimeThresholds[farmsWanted]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
