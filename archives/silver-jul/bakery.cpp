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
        while (left + d <= right && fn(left + d))
            left += d;
    }
    return left;
}
struct Bound {
    optional<long double> lower, upper;
    bool impossible;
    static Bound from_bool(bool possible) {
        if (possible) {
            return {
                nullopt, nullopt, false
            };
        } else {
            return {
                nullopt, nullopt, true
            };
        }
    }
    static Bound from_lower(long double i) {
        return {
            i, nullopt, false
        };
    }
    static Bound from_upper(long double i) {
        return {
            nullopt, i, false
        };
    }
    bool apply(pair<long double, long double>& bounds) {
        if (impossible) {
            return false;
        } else if (lower) {
            if (lower > bounds.second) {
                return false;
            }
            if (lower > bounds.first) {
                bounds.first = lower.value();
            }
        } else if (upper) {
            if (upper < bounds.first) {
                return false;
            }
            if (upper < bounds.second) {
                bounds.second = upper.value();
            }
        }
        return true;
    }
    void print() {
        if (impossible) {
            dbg("impossible bound");
        } else if (lower) {
            dbg("lower bound @", lower.value());
        } else if (upper) {
            dbg("upper bound @", upper.value());
        } else {
            dbg("no bound");
        }
    }
};
struct Friend {
    ll a, b, c;
    ll ta;
    ll tb;
    Friend() {
        a = 0;
        b = 0;
        c = 0;
    }
    Friend(ll ta, ll tb) {
        a = gnxt<ll>();
        b = gnxt<ll>();
        c = gnxt<ll>();
        this->ta = ta;
        this->tb = tb;
    }
    Bound bound(ll S) {
        ll determinant = c - a * ta - b * tb + b * S;
        if (b == a) {
            return Bound::from_bool(determinant >= 0);
        }
        if (b - a > 0) {
            return Bound::from_upper(static_cast<long double>(determinant)/static_cast<long double>(b - a));
        } else { // b - a < 0
            return Bound::from_lower(static_cast<long double>(determinant)/static_cast<long double>(b - a));
        }
        // a * (ta - x) + b * (tb - y) <= c
        // a * (ta - x) + b * (tb - S + x) <= c
        // a + ta - a * x + b * tb - b * S + b * x <= c
        // (b - a) * x <= c - a * ta - b * tb + b * S
    }
};
int main() {
    // USACO 2023 February Contest, Silver
    // Problem 1. Bakery
    // https://usaco.org/index.php?page=viewproblem2&cpid=1302
    ll ntests = gnxt<ll>();
    for (ll iii = 0; iii < ntests; iii++) {
        ll ncows = gnxt<ll>(), ta = gnxt<ll>(), tb = gnxt<ll>();
        vec<Friend> friends(ncows);
        for (auto& f: friends) {
            f = Friend(ta, tb);
        }
        auto ok = [=](ll S) {
            pair<long double, long double> bounds = make_pair(0, ta-1);
            Bound::from_lower(S-(tb-1)).apply(bounds);
            Bound::from_upper(S).apply(bounds);
            for (auto f: friends) {
                if (!f.bound(S).apply(bounds)) {
                    return false;
                }
            }
            return ceil(bounds.first) <= floor(bounds.second);
        };
        cout << bsearch(0, ta+tb-2, [=](ll k) { return !ok(k); }) + 1 << endl;
    }
}
