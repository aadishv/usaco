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
struct Pasture_Animal {
    int position_x, position_y, id;
    char direction;
};

struct Intersection {
    Pasture_Animal northbound, eastbound;
    int collision_x, collision_y;      // collision coordinates
    int north_distance, east_distance; // distance traveled before intersection
};

int main() {
    // USACO 2020 December Contest, Bronze
    // Problem 3. Stuck in a Rut
    // https://usaco.org/index.php?page=viewproblem2&cpid=1061
    int num_cows;
    cin >> num_cows;
    vector<Pasture_Animal> animals = {};
    vector<Intersection> intersections = {};
    vector<int> stopping_times(num_cows, -1);

    for (int i = 0; i < num_cows; i++) {
        char direction;
        int x, y;
        cin >> direction >> x >> y;
        Pasture_Animal animal { x, y, i, direction };
        animals.push_back(animal);
    }

    for (auto northbound: animals) {
        if (northbound.direction == 'E') {
            continue;
        }
        for (auto eastbound: animals) {
            if (eastbound.direction == 'N') {
                continue;
            }
            if (northbound.position_x > eastbound.position_x && eastbound.position_y > northbound.position_y) {
                // Calculate potential intersection
                int collision_x = northbound.position_x;
                int collision_y = eastbound.position_y;
                int north_distance = abs(northbound.position_y - collision_y);
                int east_distance = abs(eastbound.position_x - collision_x);
                intersections.push_back(Intersection { northbound, eastbound, collision_x, collision_y, north_distance, east_distance });
            }
        }
    }

    sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) {
        return min(a.north_distance, a.east_distance) < min(b.north_distance, b.east_distance);
    });

    for (auto intersection: intersections) {
        bool east_alive = stopping_times[intersection.eastbound.id] > intersection.east_distance ||
                         stopping_times[intersection.eastbound.id] == -1;
        bool north_alive = stopping_times[intersection.northbound.id] > intersection.north_distance ||
                          stopping_times[intersection.northbound.id] == -1;

        if (east_alive && north_alive) {
            if (intersection.east_distance < intersection.north_distance) {
                stopping_times[intersection.northbound.id] = intersection.north_distance;
            } else if (intersection.north_distance < intersection.east_distance) {
                stopping_times[intersection.eastbound.id] = intersection.east_distance;
            }
        }
    }

    for (int stop_time: stopping_times) {
        cout << ((stop_time == -1) ? "Infinity" : to_string(stop_time)) << endl;
    }

    return 0;
}
