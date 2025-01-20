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
    // Problem 2. Speeding Ticket
    // https://usaco.org/index.php?page=viewproblem2&cpid=568
    setIO("speeding", false);
    int num_road_segments, num_bessie_segments;
    cin >> num_road_segments >> num_bessie_segments;
    vi speed_limits = {};
    int max_speed_violation = 0;

    // Read speed limits for each road segment
    for (auto i = 0; i < num_road_segments; i++) {
        int segment_length, speed_limit;
        cin >> segment_length >> speed_limit;
        for (auto i = 0; i < segment_length; i++) {
            speed_limits.push_back(speed_limit);
        }
    }

    // Compare Bessie's speed to limits
    int current_mile = 0;
    for (auto i = 0; i < num_bessie_segments; i++) {
        int segment_length, bessie_speed;
        cin >> segment_length >> bessie_speed;
        for (auto i = 0; i < segment_length; i++) {
            int speed_difference = bessie_speed - speed_limits[current_mile];
            if (speed_difference > max_speed_violation) {
                max_speed_violation = speed_difference;
            }
            current_mile++;
        }
    }

    cout << max_speed_violation << endl;
    return 0;
}
