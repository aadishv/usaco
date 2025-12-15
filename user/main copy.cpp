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

int main() {
    int ntests = nxt();
    for (int test = 0; test < ntests; test++) {
        int n = nxt(), k = nxt();
        vi values(n); for (auto& v: values) v = nxt();
        auto check = [&](int med) -> bool {
            vi le(n); // le_i = number of values less than or equal to med
            le[0] = values[0] <= med;
            for (int i = 1; i < n; i++) {
                le[i] = le[i-1] + (values[i] <= med);
            }
            vi dp(n); // dp_i = 2 * le_i - i
            for (int i = 0; i < n; i++) dp[i] = 2 * le[i] - i;
            //  r >= l + k-1
            int l = 0;
            // inclusive range [l, r]
            for (int r = k-1; r < n; r++) {
                if (dp[r - (k-1)] < dp[l]) {
                    l = r - (k-1);
                }
                if (dp[l] <= dp[r] + 1) {
                    dbg(med, l, r);
                    return true;
                }
            }
            return false;
        };
        dbg("3");
        check(3);
        // dbg("4");
        // check(4);
    }
}
