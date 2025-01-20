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
    // USACO 2016 February Contest, Bronze
    // Problem 2. Circular Barn
    // https://usaco.org/index.php?page=viewproblem2&cpid=616
    setIO("cbarn", false);

    int numRooms = nxt();
    map<int, int> cowsPerRoom;
    for (int i = 0; i < numRooms; i++) cowsPerRoom[i] = nxt();

    int minTotalDistance = -1;
    for (int startingRoom = 0; startingRoom < numRooms; startingRoom++) {
        int totalDistance = 0;
        for (int currentRoom = 0; currentRoom < numRooms; currentRoom++) {
            int distance = 0;
            if (currentRoom >= startingRoom) {
                distance = currentRoom - startingRoom;
            } else {
                distance = currentRoom - startingRoom + numRooms;
            }
            totalDistance += distance * cowsPerRoom[currentRoom];
        }
        if (minTotalDistance == -1 || totalDistance < minTotalDistance) {
            minTotalDistance = totalDistance;
        }
    }
    cout << minTotalDistance << endl;
    return 0;
}
