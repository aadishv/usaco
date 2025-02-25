#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ball(it) it.begin(), it.begin()
#define ll long long
#define cast(a, b) static_cast<b>(a)
using namespace std;
namespace utils {
    int nxt() {int a; cin >> a; return a;};
    template<typename T>
    T gnxt() {T a; cin >> a; return a;}
    template<typename T>
    void dbgv(vector<T> vs, string id = "") {
        if (id != "") cerr << id << ":\t";
        for (auto v: vs) cerr << v << " ";
        cerr << endl;
    }
    void dbg() { cerr << endl; }  // base case
    template<typename T, typename... Args>
    void dbg(T a, Args... args) {
        cerr << a << " ";
        dbg(args...);
    }
}
using namespace utils;

int main() {
    #ifndef AADISHV
    string name = "paintbarn";
    if (name.size() > 0) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
    #endif
    int nr = nxt(), k = nxt();
    int painted[1001][1002]{{0}};
    int mx = 0, my = 0;
    for (int i = 0; i < nr; i++) {
        int x1 = nxt(), y1 = nxt(), x2 = nxt(), y2 = nxt();
        mx = max(mx, x2); my = max(my, y2);
        painted[y1+1][x1+1]++;
        painted[y2+1][x2+1]++;
        painted[y1+1][x2+1]--;
        painted[y2+1][x1+1]--;
        // for (int x = x1; x < x2; x++) {
        //     for (int y = y1; y < y2; y++) {
        //         painted[y][x]++;
        //     }
        // }
    }
    int prefix[1002][1002]{{0}};
    int total = 0;
    for (int y = 0; y <= my; y++) {
        for (int x = 0; x <= mx; x++) {
            prefix[y+1][x+1] = painted[y+1][x+1] + prefix[y][x+1] + prefix[y+1][x] - prefix[y][x];
            if (prefix[y+1][x+1] == k) total++;
        }
    }
    // for (int y = my; y >= 0; y--) {
    //     // cout << y << '\t';
    //     for (int x = 0; x < mx; x++) {
    //         // cout << painted[y][x] << " ";
    //         total += (painted[y][x] == k);
    //     }
    //     // cout << endl;
    // }
    cout << total << endl;
}
