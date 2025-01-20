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
    // USACO 2020 January Contest, Bronze
    // Problem 3. Race
    // https://usaco.org/index.php?page=viewproblem2&cpid=989
    setIO("race", true);

    unsigned long long total_race_distance, num_test_cases;
    cin >> total_race_distance >> num_test_cases;
    vector<unsigned long long> target_speeds(num_test_cases);
    for (unsigned long long i = 0; i < num_test_cases; i++) { cin >> target_speeds[i]; }
    string output_buffer = "";
    printv(target_speeds);
    for (auto target_speed: target_speeds) {
        unsigned long long forward_distance = 1;
        unsigned long long backward_distance = target_speed;
        unsigned long long forward_velocity = forward_distance;
        unsigned long long backward_velocity = backward_distance;
        unsigned long long elapsed_time = 1;

        while (forward_velocity != target_speed && !(forward_distance >= total_race_distance)) {
            forward_distance += ++forward_velocity;
            elapsed_time++;
            if (target_speed == 5) {
                cerr << forward_velocity << " " << forward_distance << " " << elapsed_time << "|";
            }
        }
        if (target_speed == 5) {
            cerr << "---" << endl;
            cerr << forward_distance + backward_distance << " " << elapsed_time << endl;
        }
        if (!(forward_distance >= total_race_distance)) {
            elapsed_time++;
            while (!(forward_distance+backward_distance >= total_race_distance) &&
                   !(forward_distance+backward_distance+forward_velocity >= total_race_distance)) {
                forward_distance += ++forward_velocity;
                backward_distance += ++backward_velocity;
                elapsed_time += 2;
            }
            if (!(forward_distance + backward_distance >= total_race_distance)) elapsed_time++;
        }
        output_buffer += to_string(elapsed_time) + "\n";
    }
    cout << output_buffer;
    return 0;
}
