#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ball(it) it.begin(), it.begin()
#define ll long long
#define cast(a, b) static_cast<b>(a)
#define vec vector
#define RANGE(a, b) for (int i = a; i < b; i++)
#define RANGE_I(a, b, c) for (int c = a; c < b; c++)
#define let auto
using namespace std;

namespace utils {
    int nxt() {
        int a;
        cin >> a;
        return a;
    };
    template <typename T> T gnxt() {
        T a;
        cin >> a;
        return a;
    }
    template <typename T>
    void dbgv(vector<T> vs, string id = "", bool use_cout = false) {
        if (id != "")
            cerr << id << ":\t";

        // Find length of longest number when stringified
        size_t max_len = 0;
        for (auto v : vs) {
            ostringstream ss;
            ss << v;
            max_len = max(max_len, ss.str().length());
        }

        // Output with padding
        for (auto v : vs) {
            ostringstream ss;
            ss << v;
            string str = ss.str();
            cerr << str << string(1 + max_len - str.length(), ' ');
        }
        cerr << endl;
    }
    template <typename T>
    void dbgv2(vector<vector<T>> vs, string id = "", bool use_cout = false) {
        if (id != "")
            cerr << id << ":\t";

        // Find length of longest number when stringified across ALL elements
        size_t max_len = 0;
        for (auto row : vs) {
            for (auto v : row) {
                ostringstream ss;
                ss << v;
                max_len = max(max_len, ss.str().length());
            }
        }

        // Output each row with consistent padding
        for (auto row : vs) {
            for (auto v : row) {
                ostringstream ss;
                ss << v;
                string str = ss.str();
                cerr << str << string(1 + max_len - str.length(), ' ');
            }
            cerr << endl;
        }
        cerr << endl;
    }
    void dbg() { cerr << endl; } // base case
    template <typename T, typename... Args> void dbg(T a, Args... args) {
        cerr << a << " ";
        dbg(args...);
    }
    template <typename T> int sum(vector<T> v) {
        T ans = 0;
        for (auto x : v)
            ans += x;
        return ans;
    }
    template <typename T> void print(vector<T> v) {
        for (auto x : v)
            cout << x << " ";
        cout << endl;
    }
} // namespace utils
using namespace utils;

int main() {
    // USACO 2014 March Contest, Silver
    // Problem 2. The Lazy Cow
    // https://usaco.org/index.php?page=viewproblem2&cpid=416
#ifndef AADISHV
    string name = "lazy";
    if (name.size() > 0) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
#endif
    int n = nxt(), k = nxt();
    vec<vec<int>> grid_og(n, vi(n, 0)); // [y][x] indexes!!!
    for (auto& row: grid_og) {
        for (auto& v: row) v = nxt();
    }
    vec<vec<int>> grid(n*2-1, vi(n*2-1, 0)); // [y][x] indexes!!!
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            grid[x-y+(n-1)][x+y] = grid_og[y][x];
        }
    }
    vec<vec<int>> prefix(n*2, vi(n*2, 0)); // [y][x] indexes!!!
    for (int y = 0; y < n*2-1; y++) {
        for (int x = 0; x < n*2-1; x++) {
            prefix[y+1][x+1] = prefix[y][x+1] + prefix[y+1][x] - prefix[y][x]
                + grid[y][x];
        }
    }
    int best = 0;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            int tx = x+y;
            int ty = x-y+(n-1);
            int x1 = max(0, tx - k);
            int y1 = max(0, ty - k);
            int x2 = min(n*2-2, tx + k);
            int y2 = min(n*2-2, ty + k);
            int sum = prefix[y2+1][x2+1] + prefix[y1][x1]
                - prefix[y2+1][x1] - prefix[y1][x2+1];
            best = max(sum, best);
        }
    }
    cout << best << endl;
}
