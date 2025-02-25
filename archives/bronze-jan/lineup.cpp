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
    // USACO 2019 December Contest, Bronze
    // Problem 3. Livestock Lineup
    // https://usaco.org/index.php?page=viewproblem2&cpid=965
    setIO("lineup", false);
    vector<string> cowNames = {"Beatrice", "Belinda", "Bella", "Bessie", "Betsy", "Blue", "Buttercup", "Sue"};
    vi cowIndices = {0,1,2,3,4,5,6,7};
    vector<pair<int, int>> constraints = {};
    int numConstraints;
    cin >> numConstraints;
    cin.ignore();

    // Helper functions to replace missing functions
    auto split = [](const string& s, char delim) {
        vector<string> tokens;
        stringstream ss(s);
        string token;
        while (getline(ss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    };

    auto findIndex = [](const vector<string>& vec, const string& val) {
        auto it = find(vec.begin(), vec.end(), val);
        if (it != vec.end()) {
            return static_cast<long>(distance(vec.begin(), it));
        }
        return static_cast<long>(-1);
    };

    for (int i = 0; i < numConstraints; i++) {
        string line;
        getline(cin, line);
        auto tokens = split(line, ' ');
        constraints.push_back(make_pair(
            findIndex(cowNames, tokens.front()),
            findIndex(cowNames, tokens.back())
        ));
    }

    do {
        bool validPermutation = true;
        for (const auto& constraint: constraints) {
            int pos1 = find(cowIndices.begin(), cowIndices.end(), constraint.first) - cowIndices.begin();
            int pos2 = find(cowIndices.begin(), cowIndices.end(), constraint.second) - cowIndices.begin();
            if (abs(pos1 - pos2) != 1) {
                validPermutation = false;
                break;
            }
        }
        if (validPermutation) {
            for (int i: cowIndices) {
                cout << cowNames[i] << endl;
            }
            break;
        }
    } while (next_permutation(all(cowIndices)));
    return 0;
}
