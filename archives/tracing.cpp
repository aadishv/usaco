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
    // https://usaco.org/index.php?page=viewproblem2&cpid=1037
    // USACO 2020 US Open Contest, Bronze
    // Problem 3. Cowntact Tracing

    setIO("tracing");

    int numCows, numInteractions;
    cin >> numCows >> numInteractions;
    cin.ignore(1);

    vector<vector<int>> interactions; // time, cow1, cow2
    vector<bool> finalInfectionState(numCows);

    // Read final infection states
    for (int i = 0; i < numCows; i++) {
        char state;
        cin >> state;
        finalInfectionState[i] = (state == '1');
    }
    cin.ignore(1);

    // Read interaction records
    for (int i = 0; i < numInteractions; i++) {
        vector<int> interaction(3);
        cin >> interaction[0] >> interaction[1] >> interaction[2];
        // Convert to 0-based indexing
        interaction[0]--;
        interaction[1]--;
        interaction[2]--;
        interactions.push_back(interaction);
    }

    // Sort interactions by time
    sort(interactions.begin(), interactions.end(),
         [](const auto& a, const auto& b) { return a[0] < b[0]; });

    int numValidPatientZeros = 0;
    int minInteractions = numInteractions;
    int maxInteractions = -1;

    // Try each cow as patient zero
    for (int patientZero = 0; patientZero < numCows; patientZero++) {
        bool validPatientZero = false;

        // Try different numbers of interactions K
        for (int k = 0; k <= numInteractions; k++) {
            vector<bool> infectedStates(numCows, false);
            vector<int> remainingInteractions(numCows, k);
            infectedStates[patientZero] = true;

            // Simulate spread of infection
            for (const auto& interaction : interactions) {
                int cow1 = interaction[1];
                int cow2 = interaction[2];
                bool spreadThisRound = false;

                if (infectedStates[cow1]) {
                    remainingInteractions[cow1]--;
                }
                if (infectedStates[cow2]) {
                    remainingInteractions[cow2]--;
                }

                if (infectedStates[cow1] && remainingInteractions[cow1] >= 0) {
                    infectedStates[cow2] = true;
                    spreadThisRound = true;
                }
                if (!spreadThisRound && infectedStates[cow2] && remainingInteractions[cow2] >= 0) {
                    infectedStates[cow1] = true;
                }
            }

            if (infectedStates == finalInfectionState) {
                validPatientZero = true;
                minInteractions = min(minInteractions, k);
                maxInteractions = max(maxInteractions, k);
            }
        }

        if (validPatientZero) {
            numValidPatientZeros++;
        }
    }

    cout << numValidPatientZeros << " "
         << (minInteractions == -1 ? 0 : minInteractions) << " "
         << (maxInteractions == numInteractions ? "Infinity" : to_string(maxInteractions))
         << endl;

    return 0;
}
