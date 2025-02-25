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
    // USACO 2015 December Contest, Bronze
    // Problem 3. Contaminated Milk
    // https://usaco.org/index.php?page=viewproblem2&cpid=569
    // note: AI was required - not to fix the program but to identify the part of the problem that I had missed
    setIO("badmilk", false);
    int numPeople = nxt(), numMilkTypes = nxt(), numDrinkEvents = nxt(), numSicknessEvents = nxt();
    map<int, map<int, int>> drinkTimestamps = {}; // milk type: { person: earliest_drink_time }
    map<int, int> sicknessTimes = {}; // person: time_of_sickness
    for (auto i = 0; i < numDrinkEvents; i++) {
        int personId = nxt(), milkType = nxt(), timestamp = nxt();
        if (drinkTimestamps[milkType][personId] == 0 || timestamp < drinkTimestamps[milkType][personId]) {
            drinkTimestamps[milkType][personId] = timestamp;
        }
    }
    for (auto i = 0; i < numSicknessEvents; i++) {
        int personId = nxt(), timestamp = nxt();
        sicknessTimes[personId] = timestamp;
    }
    int maxPotentiallyInfected = 0;
    for (auto suspectMilk = 1; suspectMilk <= numMilkTypes; suspectMilk++) {
        bool couldBeBadMilk = true;
        // check that every sick person drank before getting sick
        auto drinkEvents = drinkTimestamps[suspectMilk];
        for (auto sickEvent: sicknessTimes) {
            if (drinkEvents.count(sickEvent.first)) {
                if (!(drinkEvents[sickEvent.first] < sickEvent.second)) {
                    couldBeBadMilk = false;
                }
            } else {
                couldBeBadMilk = false;
            }
        }
        if (!couldBeBadMilk) continue;
        // cout << "good" << endl;
        set<int> potentialVictims = {};
        for (auto drinkEvent: drinkTimestamps[suspectMilk]) {
            potentialVictims.insert(drinkEvent.first);
        }
        maxPotentiallyInfected = max(maxPotentiallyInfected, static_cast<int>(potentialVictims.size()));
    }
    cout << maxPotentiallyInfected << endl;
    return 0;
}
