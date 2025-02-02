#include <bits/stdc++.h>
#define vi vector<int>
#define ll long long
#define all(i) i.begin(), i.end()
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
enum Poss {OG = 0, NEW_MOVED = 1, EITHER = 2};
void solve_case() {
    int dim = nxt(), xshift = nxt(), yshift = nxt();
    map<pair<int, int>, vector<Poss>> options = {};
    set<pair<int, int>> ones = {}, twos = {};
    for (int y = 0; y < dim; y++) {
        for (int x = 0; x < dim; x++) {
            char c; cin >> c;
            int n = (c == 'W' ? 0 : c == 'G' ? 1 : 2);
            if (n == 2) {
                // one og, one new
                options[make_pair(x, y)] = { Poss::OG, Poss::NEW_MOVED };
                twos.insert(make_pair(x, y));
            } else if (n == 1) {
                // could be anything
                options[make_pair(x, y)] =
                    { Poss::EITHER };
                ones.insert(make_pair(x, y));
            }
        }
    }
    auto fix_op = [&](int x, int y, Poss v) {
        if (x < 0 || x >= dim || y < 0 || y >= dim) return false;
        for (int i = 0; i < options[make_pair(x, y)].size(); i++) {
            auto& l = options[make_pair(x, y)][i];
            if (l == v || l == Poss::EITHER) {
                options[make_pair(x, y)][i] = v;
                return true;
            }
        }
        return false;
    };
    // handle count 2
    for (auto c: twos) {
        // handle the first one
        auto result = fix_op(c.first-xshift, c.second-yshift, Poss::OG);
        if (!result) {
            // this is BAD
            cout << -1 << endl;
            return;
        }
    }
    // handle first
    // try to find something which can be explained as a superimposed version
    for (auto c: options) {
        auto x = c.first.first;
        auto y = c.first.second;
        auto option = c.second;
        if (option.size() == 0) continue;
        if (option[0] == Poss::OG || option[0] == Poss::EITHER) {
            // it's possible that this was the start of a movement
            int nx = x + xshift;
            int ny = y + yshift;
            bool result = fix_op(nx, ny, Poss::NEW_MOVED);
            if (!result) {
                // this cannot be superimposed,
                options[make_pair(x, y)][0] = Poss::OG;
            } else {
                options[make_pair(x, y)][0] = Poss::OG;
            }
        }
    }
    int total = 0;
    for (int x = 0; x < dim; x++) {
        for (int y = 0; y < dim; y++) {
            for (auto v: options[make_pair(x, y)]) {
                if (v == Poss::OG || v == Poss::EITHER) {
                    total++;
                }
            }
        }
    }
    cout << total << endl;
    return;
}
int main() {
    // astral superposition -- OLD
    int ntestcases = nxt();
    for (int t = 0; t < ntestcases; t++) {
        // cout << "b";
        solve_case();
        // cout << "e" << endl;
    }
}
