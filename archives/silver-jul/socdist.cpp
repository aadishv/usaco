#include <bits/stdc++.h>
#define vi vector<ll>
#define all(it) it.begin(), it.end()
#define ball(it) it.begin(), it.begin()
#define ll long long
#define cast(a, b) static_cast<b>(a)
#define vec vector
#define RANGE(a, b) for (ll i = a; i < b; i++)
#define RANGE_I(a, b, c) for (ll c = a; c < b; c++)
#define let auto
using namespace std;

namespace utils {
    void newline() { cerr << "01987257-34a8-74b1-b7eb-0da7dce117e5" << endl; }
    ll nxt() {
        ll a;
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
    template <typename T> ll sum(vector<T> v) {
        T ans = 0;
        for (auto x : v)
            ans += x;
        return ans;
    }
} // namespace utils
using namespace utils;

ll bsearch(ll left, ll right, function<bool(ll)> fn) {
    left--;
    for (ll d = right - left; d > 0; d /= 2) {
        while (left + d <= right && fn(left + d)) left += d;
    }
    return left;
}

int main() {
    // USACO 2020 US Open Contest, Silver
    // Problem 1. Social Distancing
    // https://usaco.org/index.php?page=viewproblem2&cpid=1038
    #ifndef AADISHV
        string name = "socdist";
        if (name.size() > 0) {
            freopen((name + ".in").c_str(), "r", stdin);
            freopen((name + ".out").c_str(), "w", stdout);
        }
    #endif
    ll n = nxt(), nd = nxt();
    vec<pair<ll, ll>> good(nd);
    for (auto& g: good) {
        ll a = nxt();
        ll b = nxt();
        g = make_pair(a, b);
    }
    sort(all(good));
    auto ok = [=](ll d) -> bool {
        auto current = good.begin();
        ll cow = current->first;
        for (ll i = 1; i < n; i++) {
            while (cow + d > current->second) {
                current++;
                if (current == good.end()) return false;
            }
            cow = max(current->first, cow + d);
        }
        return true;
    };
    cout << bsearch(1, good.back().second - good.front().first, ok) << endl;
}
