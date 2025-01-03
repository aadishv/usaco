#include <bits/stdc++.h>
using namespace std;

void setIO(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

int main() {
    // https://usaco.org/index.php?page=viewproblem2&cpid=1037
    // USACO 2020 US Open Contest, Bronze
    // Problem 3. Cowntact Tracing

    setIO("tracing");

    int ncows;
    int ninteractions;
    cin >> ncows >> ninteractions;
    cin.ignore(1);
    vector<vector<int>> interactions = {}; // t, x++, y++
    vector<bool> cowgood(ncows);
    for (int i = 0; i < ncows; i++) {
        char c;
        cin >> c;
        cowgood[i] = c=='1';
    }
    cin.ignore(1);
    for (int i = 0; i < ninteractions; i++) {
        vector<int> interaction(3);
        cin >> interaction[0] >> interaction[1] >> interaction[2];
        interaction[0]--;
        interaction[1]--;
        interaction[2]--;
        interactions.push_back(interaction);
    }
    std::sort(interactions.begin(), interactions.end(), [=](const auto inter1, const auto inter2) {
        return inter1[0] < inter2[0];
    });
    int numb_cands = 0;
    int min_k = ninteractions;
    int max_k = -1;
    for (int candidate = 0; candidate < ncows; candidate++) {
        bool found = false;
        for (int k = 0; k <= ninteractions; k++) {
            // time for the hard part: simulation
            vector<bool> infected(ncows, false);
            vector<int> timer(ncows, k);
            infected[candidate] = true;
            for (auto interaction: interactions) {
                // simulate step (aka interaction)
                int ai = interaction[1];
                int bi = interaction[2];
                bool changedthisround = false;
                if (infected[ai])
                    timer[ai]--;
                if (infected[bi])
                    timer[bi]--;
                if (infected[ai] && timer[ai] >= 0) {
                    infected[bi] = true;
                    changedthisround = true;
                }
                if (!changedthisround) {
                    if (infected[bi] && timer[bi] >= 0) {
                        infected[ai] = true;
                    }
                }
            }
            if (infected == cowgood) {
                found = true;
                if (k < min_k) {
                    min_k = k;
                }
                if (k > max_k) {
                    max_k = k;
                }
            }
        }
        if (found) {
            numb_cands++;
        }
    }
    cout << numb_cands << " " << (min_k == -1 ? 0 : min_k) << " " << ((max_k == ninteractions) ? "Infinity" : to_string(max_k)) << endl;
    return 0;
}
