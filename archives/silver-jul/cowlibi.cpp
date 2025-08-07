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

struct Alibi {
    ll time;
    ll x;
    ll y;
};

bool operator<(const Alibi &a, const Alibi &b) { return a.time < b.time; }
bool operator>(const Alibi &a, const Alibi &b) { return a.time > b.time; }
bool operator==(const Alibi &a, const Alibi &b) { return (a.time == b.time) && (a.x == b.x) && (a.y == b.y); }
// bool possible(const Alibi &p1, const Alibi &p2) {
//     return abs(p1.x - p2.x) + abs(p1.y - p2.y) <= abs(p2.time - p1.time);
// }
bool possible(const Alibi &p1, const Alibi &p2) {
    ll dx = p1.x - p2.x;
    ll dy = p1.y - p2.y;
    ll dt = abs(p2.time - p1.time);
    // compare squared Euclidean distance <= (dt)^2
    return dx*dx + dy*dy <= dt*dt;
}
Alibi from_in() {
    ll x = nxt(), y = nxt(), t = nxt();
    return Alibi{t, x, y};
}

int main() {
    // USACO 2023 February Contest, Silver
    // Problem 2. Cow-libi
    // https://usaco.org/index.php?page=viewproblem2&cpid=1303#
    ll nm = nxt(), na = nxt();
    vec<Alibi> killings(nm);
    for (auto &k : killings) {
        k = from_in();
    }
    sort(all(killings));
    ll n = 0;
    for (ll i = 0; i < na; i++) {
        Alibi alibi = from_in();
        bool good = false;
        vec<Alibi> check = {};
        if (alibi.time < killings.front().time) {
            check = {killings.front()};
        } else if (alibi.time > killings.back().time) {
            check = {killings.back()};
        } else {
            auto upper = lower_bound(all(killings), alibi);
            if (upper->time == alibi.time) {
                good = upper->x != alibi.x || upper->y != alibi.y;
            } else {
                auto lower = prev(upper);
                check = {*lower, *upper};
            }
        }
        for (auto& garden: check) {
            if (!possible(alibi, garden)) {
                good = true;
            }
        }
        n += good;
    }
    cout << n << endl;
}
