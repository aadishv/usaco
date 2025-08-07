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
    void newline() { cerr << "01987257-34a8-74b1-b7eb-0da7dce117e5" << endl; }
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
        newline();
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
            newline();
        }
        newline();
    }
    void dbg() { newline(); } // base case
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
} // namespace utils
using namespace utils;

int bsearch(int l, int r, function<bool(int)> f) {
    // f(i) exists for i in [l, r]
    l--;
    // f(l) == true is an invariant
    for (int spacing = r - l; spacing > 0; spacing /= 2) {
        while (l + spacing <= r && f(l + spacing)) l += spacing;
    }
    return l;
}

int main() {
    // USACO 2016 January Contest, Silver
    // Problem 1. Angry Cows
    // https://usaco.org/index.php?page=viewproblem2&cpid=594
    #ifndef AADISHV
        string name = "angry";
        if (name.size() > 0) {
            freopen((name + ".in").c_str(), "r", stdin);
            freopen((name + ".out").c_str(), "w", stdout);
        }
    #endif
    int n = nxt(), k = nxt();
    vi cows(n);
    for (auto& c: cows) c = nxt();
    sort(all(cows));
    auto good = [=](int l) {
        size_t left = 0;
        for (int c = 0; c < k; c++) {
            auto o = left;
            while (left < cows.size() && cows[o] + 2*l + 1 > cows[left]) left++;
            if (left == cows.size()) {
                return true;
            }
        }
        return false;
    };
    cout << bsearch(0, cows.back() - cows.front(), [=](int p) {
        return !good(p);
    })+1 << endl;
}
