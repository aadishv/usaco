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

ll nxt() {ll a; cin >> a; return a;}

int main() {
    // it's mooin time II
    ll number = nxt();
    map<ll, set<ll>> counts = {};
    set<ll> found = {};
    vector<ll> counthist = {0};
    int t = 0;
    vector<ll> ns(number); for (auto& n: ns) {
        n = nxt();
        found.insert(n);
        counts[n].insert(t);
        counthist.push_back(found.size());
        t++;
    }
    map<ll, set<ll>> options = {};
    ll final = 0;
    for (auto option: counts) {
        auto size = option.second.size();
        if (size >= 2) {
            set<ll>::iterator l = option.second.end();
            advance(l, -2);
            final += counthist[*(l)] - (size > 2);
        }
    }
    cout << final << endl;
}
// 808608712
