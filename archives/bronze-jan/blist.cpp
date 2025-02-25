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
    // USACO 2018 December Contest, Bronze
    // Problem 2. The Bucket List
    // https://usaco.org/index.php?page=viewproblem2&cpid=856

    setIO("blist", false);
    // In this example, FJ needs 4 buckets: He uses buckets 1 and 2 for milking cow 3 (starting at time 2). He uses bucket 3 for milking cow 1 (starting at time 4). When cow 2 arrives at time 8, buckets 1 and 2 are now available, but not bucket 3, so he uses buckets 1, 2, and 4
    vector<int> availableBuckets;
    for (auto i = 0; i < 1000; i++) { availableBuckets.push_back(i); };

    int numberOfCows = nxt();
    vector<vi> cowSchedules(numberOfCows);
    for (auto& cowSchedule: cowSchedules) {
        cowSchedule = {nxt()-1, nxt()-1, nxt()};
    }
    vector<vector<bool>> bucketTimeMatrix(1000);
    for (auto& timeSlot: bucketTimeMatrix) { timeSlot = vector<bool>(1000, false); }
    sort(all(cowSchedules), [](const auto startTime1, const auto startTime2) {
        return startTime1[0] < startTime2[0];
    });
    // false means open, true means taken
    for (auto schedule: cowSchedules) {
        vi assignedBuckets(schedule[2]);
        vector<bool> startTimeAvailability = bucketTimeMatrix[schedule[0]];
        auto bucketPtr = startTimeAvailability.begin();
        for (auto& bucket: assignedBuckets) {
            while (*bucketPtr) bucketPtr++;
            bucket = bucketPtr-startTimeAvailability.begin();
            bucketPtr++;
        }

        for (int time = schedule[0]; time <= schedule[1]; time++) {
            for (auto bucketNum: assignedBuckets) {
                bucketTimeMatrix[time][bucketNum] = true;
            }
        }
    }

    int maxBucketsNeeded = 1;
    for (int timeSlot = 0; timeSlot < 1000; timeSlot++) {
        auto bucketPtr = bucketTimeMatrix[timeSlot].end()-1;
        while (!*bucketPtr && bucketPtr != bucketTimeMatrix[timeSlot].begin()) bucketPtr--;
        int bucketsInUse = bucketPtr-bucketTimeMatrix[timeSlot].begin() + 1;
        if (bucketsInUse > maxBucketsNeeded) {
            maxBucketsNeeded = bucketsInUse;
        }
    }
    cout << maxBucketsNeeded << endl;
    return 0;
}
