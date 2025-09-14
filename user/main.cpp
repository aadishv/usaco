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

struct Solver {
    set<int> values;
    bool solve(float start, float r) {
        pair<float, float> range = make_pair(start, start);
        while (r >= 1) {
            int initial = *lower_bound(all(values), get<0>(range)-r);
            auto final_it = upper_bound(all(values), get<1>(range)+r);
            if (final_it == values.begin()) return false;
            auto final = *(--final_it);
            if (!(initial < get<0>(range) || initial == *values.begin())) return false;
            if (!(final > get<1>(range) || final == *(--values.end()))) return false;
            range = make_pair(initial, final);
            r -= 1;
        }
        return get<0>(range) == *values.begin() && get<1>(range) == *(--values.end());
    }
};
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
    for (auto& v: values) v = nxt();
    sort(all(values));
    Solver solver { set<int>(all(values)) };
    vec<float> check(all(values));
    for (int i = 0; i < n - 1; i++) {
        check.push_back((static_cast<float>(values[i]) + static_cast<float>(values[i+1])) / 2);
    }
    float best = values.back() - values.front();
    for (auto start: check) {
        int result_unadjusted = bsearch(2, 2 * (values.back() - values.front()), [&](const int a) {
            return !solver.solve(start, static_cast<float>(a) / 2);
        })+1;
        float result = static_cast<float>(result_unadjusted) / 2;
        best = min(best, result);
    }
    cout << std::fixed << std::setprecision(1) << best << endl;
}
