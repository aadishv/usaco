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
    // USACO 2016 US Open Contest, Silver
    // Problem 2. Diamond Collector
    // https://usaco.org/index.php?page=viewproblem2&cpid=643
#ifndef AADISHV
    string name = "diamond";
    if (name.size() > 0) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
#endif
    int n = nxt(), k = nxt();
    vi arr(n); for (auto& e: arr) e = nxt();
    sort(all(arr));
    dbgv(arr);
    vi prefix(n+1, 0);
    int l = 0;
    for (int r = 0; r < n; r++) {
        while (arr[r] - arr[l] > k) l++;
        prefix[r+1] = max(prefix[r], r - l + 1);
    }
    dbgv(prefix);
    vi suffix(n+1, 0);
    int r = n-1;
    for (int l = n-1; l >= 0; l--) {
        while (arr[r] - arr[l] > k) r--;
        suffix[l] = max(suffix[l+1], r - l + 1);
    }
    dbgv(suffix);
    int best = 0;
    for (int c = 0; c < n; c++) {
        best = max(best, prefix[c] + suffix[c]);
    }
    cout << best << endl;
}
