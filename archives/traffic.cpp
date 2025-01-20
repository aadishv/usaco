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

struct TrafficSensor {
    string sensorType;
    int lowerBound, upperBound;
    pair<int, int> updateFlowRange(pair<int, int> flowRange, bool reversed = false) {
        if (sensorType == "none") {
            return { max(flowRange.first, lowerBound), min(flowRange.second, upperBound) };
        } else if ((sensorType == "on" && !reversed) || (sensorType == "off" && reversed)) {
            return { max(flowRange.first + lowerBound, 0), flowRange.second + upperBound };
        } else {
            return { max(flowRange.first - upperBound, 0), flowRange.second - lowerBound };
        }
    }
};
int main() {
    // USACO 2019 February Contest, Bronze
    // Problem 3. Measuring Traffic
    // https://usaco.org/index.php?page=viewproblem2&cpid=917
    setIO("traffic", false);
    int numSensors = nxt();
    vector<TrafficSensor> sensors(numSensors);
    for (auto& sensor: sensors) {
        string sensorType; cin >> sensorType;
        int lower, upper; lower = nxt(); upper = nxt();
        sensor = {sensorType, lower, upper};
    }

    auto reversedSensors = sensors;
    reverse(all(reversedSensors));
    pair<int, int> backwardFlow = {0, 1000};
    for (auto sensor: reversedSensors) backwardFlow = sensor.updateFlowRange(backwardFlow, true);
    cout << backwardFlow.first << " " << backwardFlow.second << endl;

    pair<int, int> forwardFlow = {1, 1000};
    for (auto sensor: sensors) forwardFlow = sensor.updateFlowRange(forwardFlow);
    cout << forwardFlow.first << " " << forwardFlow.second << endl;
    return 0;
}
