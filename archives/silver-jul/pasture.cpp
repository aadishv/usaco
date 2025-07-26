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
// const int SIZE = 10; // 2500
int main() {
    // USACO 2020 December Contest, Silver
    // Problem 2. Rectangular Pasture
    // https://usaco.org/index.php?page=viewproblem2&cpid=1063
    int ncows = nxt();
    vector<pair<int, int>> cows_vec = {};
    for (int i = 0; i < ncows; i++) {
        cows_vec.push_back(make_pair(nxt()-1, nxt()-1));
    }
    // from usaco.guide solution -- coordinate compression
    sort(cows_vec.begin(), cows_vec.end());  // sort by x
	map<int, int> reduced_x;
	for (int c = 0; c < ncows; c++) { reduced_x[cows_vec[c].first] = c; }
	auto cmp = [&](const pair<int, int> &c1, const pair<int, int> &c2) {
		return c1.second < c2.second;
	};
	sort(cows_vec.begin(), cows_vec.end(), cmp);  // sort by y
	map<int, int> reduced_y;
	for (int c = 0; c < ncows; c++) { reduced_y[cows_vec[c].second] = c; }
	for (auto &[x, y] : cows_vec) {
		x = reduced_x[x];
		y = reduced_y[y];
	}
	sort(cows_vec.begin(), cows_vec.end());
	set<pair<int, int>> cows(all(cows_vec));
	//
    vec<vi> prefix(ncows + 1, vi(ncows + 1, 0));
    for (int y = 0; y < ncows; y++) {
        for (int x = 0; x < ncows; x++) {
            int cow = cows.count(make_pair(x, y));
            prefix[y+1][x+1] = cow + prefix[y][x+1] + prefix[y+1][x] - prefix[y][x];
        }
    }
    //
    long long n = 0;
    for (int c1 = 0; c1 < ncows-1; c1++) {
        for (int c2 = c1+1; c2 < ncows; c2++) {
            auto cow1 = cows_vec[c1], cow2 = cows_vec[c2];
            int x1 = min(cow1.first, cow2.first);
            int x2 = max(cow1.first, cow2.first);
            int y1 = min(cow1.second, cow2.second);
            int y2 = max(cow1.second, cow2.second);
            int above = prefix[ncows][x2] + prefix[y2+1][x1+1] - prefix[ncows][x1+1] - prefix[y2+1][x2];
            int below = prefix[y1][x2] - prefix[y1][x1+1];
            n += (above + 1) * (below + 1);
        }
    }
    n += ncows + 1;
    cout << n << endl;
}
