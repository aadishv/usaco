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
    // USACO 2016 January Contest, Silver
    // Problem 2. Subsequences Summing to Sevens
    // https://usaco.org/index.php?page=viewproblem2&cpid=595
    #ifndef AADISHV
        string name = "div7";
        if (name.size() > 0) {
            freopen((name + ".in").c_str(), "r", stdin);
            freopen((name + ".out").c_str(), "w", stdout);
        }
    #endif
    ll n = nxt();
    vec<ll> b(n+1, 0);
    ll m = 0;
    for (int i = 1; i < n; i++) {
        b[i] = nxt() + b[i-1];
        for (ll j = 0; j < i; j++) {
            if ((b[j]-b[i]) % 7 == 0) {
                m = max(i - j, m);
                break;
            }
        }
    }
    cout << m << endl;
}
