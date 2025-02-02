#include <bits/stdc++.h>
#define vi vector<int>
#define ll long long
#define all(i) i.begin(), i.end()
#define cast static_cast
#define DEBUG_MODE true

using namespace std;

template<typename T>
void dbg(vector<T> vs, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    for (auto v: vs) cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}
template<typename T>
void dbg(T v, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}

int nxt() {int a; cin >> a; return a;}

void solve_case() {
    int dim = nxt();
    int shift = nxt()+nxt()*dim;
    vector<int> state(dim*dim, 0); // 1 possible, 2 BAD!, 3 definite
    int total = 0;
    for (int y = 0; y < dim; y++) {
        string line; cin >> line;
        // cout << line.size() << endl;
        for (int x = 0; x < dim; x++) {
            int coord = x + y * dim;
            if (line[x] != 'W') {
                state[coord]++;
                total++;
            }
            if (line[x] == 'B' && coord >= shift) {
                state[coord-shift] += 2;
            }
        }
    }
    // 11.8 -> 8.75 -> 3.08
    if (shift == 0) {
        cout << total << endl;
        return;
    }
    for (int c = 0; c < dim * dim; c++) {
        if (state[c] == 2) {
            cout << -1 << endl;
            return;
        }
        if (state[c] == 1) {
            auto nextup = c+shift;
            if (state[nextup] == 1) {
                state[nextup] = 0; total--;
            }
            state[c] = 3;
        }
    }
    cout << total << endl;
    return;
    // 0.58
}
int main() {
    // astral superposition -- WORKING => need to test on the website Tue
    int ntestcases = nxt();
    for (int t = 0; t < ntestcases; t++) {
        solve_case();
    }
}
