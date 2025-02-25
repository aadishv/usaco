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
struct MilkMeasurement {
    int timestamp;
    string cowName;
    int milkChange;
};

int main() {
    // USACO 2017 December Contest, Bronze
    // Problem 3. Milk Measurement
    // https://usaco.org/index.php?page=viewproblem2&cpid=761

    setIO("measurement", false);
    int totalMeasurements = nxt();
    vector<MilkMeasurement> measurements = {};
    map<string, int> milkProduction = {{"Bessie", 7}, {"Elsie", 7}, {"Mildred", 7}};

    for (int i = 0; i < totalMeasurements; i++) {
        int timestamp = nxt();
        string cowName; cin >> cowName;
        char direction; cin >> direction;
        if (direction == '+') {
            measurements.push_back({ timestamp, cowName, nxt() });
        } else {
            measurements.push_back({ timestamp, cowName, -abs(nxt()) });
        }
    }

    set<string> topProducers = {"Bessie", "Elsie", "Mildred"};
    int displayUpdateCount = 0;

    for (int currentTime = 0; currentTime < 101; currentTime++) {
        for (auto measurement: measurements) {
            if (measurement.timestamp == currentTime) {
                milkProduction[measurement.cowName] += measurement.milkChange;
            }
        }

        int highestProduction = max_element(all(milkProduction), [](const auto a, const auto b) {
            return a.second < b.second;
        })->second;

        set<string> newTopProducers = {};
        for (auto producer: milkProduction) {
            if (producer.second == highestProduction) {
                newTopProducers.insert(producer.first);
            }
        }

        if (topProducers != newTopProducers) {
            displayUpdateCount++;
            topProducers = newTopProducers;
        }
    }

    cout << displayUpdateCount << endl;
    return 0;
}
