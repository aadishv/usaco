#include <algorithm>
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

        size_t max_len = 0;
        for (auto v : vs) {
            ostringstream ss;
            ss << v;
            max_len = max(max_len, ss.str().length());
        }

        for (auto v : vs) {
            ostringstream ss;
            ss << v;
            string str = ss.str();
            cerr << str << string(1 + max_len - str.length(), ' ');
        }
        cerr << endl;
    }
    template <typename InputIt>
    void dbgit(InputIt first, InputIt last, const std::string& id = "", bool use_cout = false) {
        std::ostream& out = use_cout ? std::cout : std::cerr;
        if (!id.empty()) out << id << ":\t";

        // Buffer stringified values (safe for single-pass iterators).
        std::vector<std::string> strs;
        size_t max_len = 0;
        for (auto it = first; it != last; ++it) {
            std::ostringstream ss;
            ss << *it;
            strs.push_back(ss.str());
            max_len = std::max(max_len, strs.back().length());
        }

        // Output with padding similar to your original function.
        for (const auto& str : strs) {
            out << str << std::string(1 + (max_len - str.length()), ' ');
        }
        out << '\n';
    }
    template <typename T>
    void dbgv2(vector<vector<T>> vs, string id = "", bool use_cout = false) {
        if (id != "")
            cerr << id << ":\t";

        size_t max_len = 0;
        for (auto row : vs) {
            for (auto v : row) {
                ostringstream ss;
                ss << v;
                max_len = max(max_len, ss.str().length());
            }
        }

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
} // namespace utils
using namespace utils;

// more of binary jumping(?) then bsearch but oh well
int bsearch(int left, int right, function<bool(int)> fn) {
    left--;
    for (int d = right - left; d > 0; d /= 2) {
        while (left + d <= right && fn(left + d)) left += d;
    }
    return left;
}

int main() {
#ifndef AADISHV
    string name = "angry";
    if (name.size() > 0) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
#endif
    auto n = nxt();
    if (n == 1) {
        cout << "0.0" << endl;
        return 0;
    }
    vector<int> values(n);
    // we're working in double space let's go lol
    for (auto& v: values) v = nxt()*2;
    sort(all(values));
    // dp
    int endpoint = 0; // where the explosion reaches, index
    vi dpl(n, 0);
    auto best_l = [&](int end, int i) -> int { return max(dpl[end]+2, values[i]-values[end]); };
    for (int i = 1; i < n; i++) {
        while (best_l(endpoint + 1, i) <= best_l(endpoint, i) && endpoint < i-1) {
            endpoint++;
        }
        dpl[i] = best_l(endpoint, i);
    }
    vi dpr(n, 0);
    endpoint = n-1;
    auto best_r = [&](int end, int i) -> int { return max(dpr[end]+2, values[end]-values[i]); };
    for (int i = n-2; i >= 0; i--) {
        while (best_r(endpoint - 1, i) < best_r(endpoint, i) && endpoint > i+1) endpoint--;
        dpr[i] = best_r(endpoint, i);
    }
    int radius = bsearch(1, 2 * (values.back() - values.front()), [&](const int radius) {
        bool found = false;
        for (int r = 1; r < n && !found; r++) {
            // we detonate at some point between values[l] and values[r],
            // presumably their midpoint (to maximize range)
            int l = lower_bound(values.begin(), values.begin() + r, values[r] - radius * 2) - values.begin();
            if ((radius-2 >= dpl[l]) && (radius-2 >= dpr[r])) found = true;
        }
        for (int i = 0; i < n && !found; i++) {
            if (radius >= dpl[i] && radius >= dpr[i]) found = true;
        }
        return !found;
    })+1;
    cout << std::fixed << std::setprecision(1) << static_cast<double>(radius) / 2.0 << endl;
}
