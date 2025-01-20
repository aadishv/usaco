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

struct Position {
    int x, y, index;
    char direction;
};

struct CollisionEvent {
    Position northCow, eastCow;
    int collisionX, collisionY;
    int northDistance, eastDistance;  // Distance traveled before collision
};

bool isInCircularRange(int value, int rangeStart, int rangeEnd) {
    if (rangeStart <= rangeEnd) {
        return rangeStart < value && value < rangeEnd;
    } else {
        return value > rangeStart || value < rangeEnd;
    }
}

int main() {
    // USACO 2017 US Open Contest, Silver
    // Problem 2. Bovine Genomics
    // https://usaco.org/index.php?page=viewproblem2&cpid=739
    setIO("cownomics");
    int numCows, numPositions;
    cin >> numCows >> numPositions;
    cin.ignore(1);

    vector<string> spottyCows;
    vector<string> plainCows;

    for (int i = 0; i < numCows; i++) {
        string genome;
        getline(cin, genome);
        spottyCows.push_back(genome);
    }

    for (int i = 0; i < numCows; i++) {
        string genome;
        getline(cin, genome);
        plainCows.push_back(genome);
    }

    int possiblePositions = 0;
    for (int pos1 = 0; pos1 < numPositions; pos1++) {
        for (int pos2 = pos1+1; pos2 < numPositions; pos2++) {
            for (int pos3 = pos2+1; pos3 < numPositions; pos3++) {
                set<vector<char>> spottyGenomes;
                for (const string& genome : spottyCows) {
                    spottyGenomes.insert({genome[pos1], genome[pos2], genome[pos3]});
                }

                bool isValid = true;
                for (const string& genome : plainCows) {
                    vector<char> genomeTriple = {genome[pos1], genome[pos2], genome[pos3]};
                    if (spottyGenomes.count(genomeTriple) > 0) {
                        isValid = false;
                        break;
                    }
                }
                possiblePositions += isValid;
            }
        }
    }
    cout << possiblePositions << endl;
    /*
    1. find all collisions
    2. sort collisions by what time the cow stops
    3. go through each collission, check if still possible based on death time,
       and update death time for that cow
    */

    return 0;
}
