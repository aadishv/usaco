#include <bits/stdc++.h>
#define ITER(v) v.begin(), v.end()
using namespace std;

void setIO(string name = ""){
    if (name.size() > 0){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}

int main() {
    // https://usaco.org/index.php?page=viewproblem2&cpid=592
    // USACO 2016 January Contest, Bronze
    // Problem 2. Angry Cows

    setIO("angry");
    int l;
    cin >> l;
    vector<int> numbers(l);

    for (int i = 0; i < l; i++) {
        cin >> numbers[i];
    }
    // cout << "\n\n\n";
    int best = -1;
    for (int candidate = 0; candidate < l; candidate++) {
        vector<int> timers(l, 0);
        timers[candidate] = 1;
        for (int i = 0; i < l; i++) {
            // cout << endl;
            auto newt = timers;
            // this is one iteration of the explosion spread
            for (int j = 0; j < l; j++) {
                for (int k = 0; k < l; k++) {
                    if (abs(numbers[j]-numbers[k]) <= timers[j]) {
                        if (timers[k] == 0 && j != k) {
                            // cout << j << k << numbers[j] << numbers[k] << timers[j] << endl;
                            newt[k] = timers[j] + 1;
                        }
                    }
                }
            }
            timers = newt;
        }
        int total = 0;
        for (int t: timers) {
            if (t > 0) {
                total++;
            }
        }
        best = max(total, best);
    }
    cout << best << endl;
    return 0;
}
