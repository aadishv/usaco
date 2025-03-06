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
#ifndef AADISHV
    string name = "paintbarn";
    if (name.size() > 0) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
#endif
    int number_rects = nxt(), k = nxt();
    vec<vi> initial(
        202, vi(202, 0)); // 2d; this contains the numbers of layers of paint
    vec<vi> prefix(201,
                   vi(201, 0)); // 2d; this contains the 1 for K-1 and -1 for K
    for (int i = 0; i < number_rects; i++) {
        int x1 = nxt() + 1, y1 = nxt() + 1, x2 = nxt() + 1, y2 = nxt() + 1;
        initial[y1][x1] += 1;
        initial[y2][x2] += 1;
        initial[y1][x2] += -1;
        initial[y2][x1] += -1;
    }
    // for (int y = 0; y < 201; y++) {
    //     for (int x = 0; x < 201; x++) {
    //         if (y < 20 && x < 20)
    //             cerr << initial[y][x] << " ";
    //     }
    //     cerr << endl;
    // }
    int countup = 0;
    for (int y = 1; y < 201; y++) {
        for (int x = 1; x < 201; x++) {
            initial[y][x] +=
                initial[y - 1][x] + initial[y][x - 1] - initial[y - 1][x - 1];
            int value =
                initial[y][x] == k ? -1 : (initial[y][x] == k - 1 ? 1 : 0);
            prefix[y][x] = prefix[y - 1][x] + prefix[y][x - 1] -
                           prefix[y - 1][x - 1] + value;
            countup += value == -1;
        }
    }
    /*
    Do this (and then repeat but with rows & columns switched):
    Go through every pair of ordered columns:
    (col1 in [0, 200), col2 in [col1, 200), row is [col1, col2])
    (i.e., if col1 is 0 and col2 is 0, row only includes col 0)
    (i.e., if col1 is 0 and col2 is 199, row includes all cols)
    1. Use O(n) system to calc sum vector <- abstracted into `row` and `column`
        functions
    2. Run Kadane's on it
    3. Update maximums
    */
    auto get_row = [=](int row, int start, int end) -> int {
        // row, start, end is in [0, 200)
        return prefix[row + 1][end + 1] + prefix[row][start] -
               prefix[row + 1][start] -
               prefix[row][end + 1]; // no need to subtract 1 from start because
                                     // of the quirks of the prefix sum array
    };
    auto get_column = [=](int column, int start, int end) -> int {
        // column, start, end is in [0, 200)
        int v =
            prefix[end + 1][column + 1] + prefix[start][column] -
            prefix[start][column + 1] -
            prefix[end + 1][column]; // no need to subtract 1 from start because
                                     // of the quirks of the prefix sum array
        return v;
    };
    // i.e., leftbest[i] is the maximum rectangle whose left side is i (i.e.,
    // col1 = i)
    vi topbest(200, 0), endbest(200, 0), leftbest(200, 0), rightbest(200, 0);
    for (int col1 = 0; col1 < 200; col1++) {
        for (int col2 = col1; col2 < 200; col2++) {
            // row is [col1, col2]
            // calculate the best for this column range
            int best = 0;
            int current = 0;
            for (int row = 0; row < 200; row++) {
                current = max(current + get_row(row, col1, col2), 0);
                best = max(best, current);
            }
            // update maximums
            leftbest[col2] = max(leftbest[col2], best);
            rightbest[col1] = max(rightbest[col1], best);

            // switching to the other way around -- don't even *try* to get an
            // intution for this your brain WILL hurt
            // calculate the best for this row range
            best = 0;
            current = 0;
            auto row1 = col1, row2 = col2;
            for (int column = 0; column < 200; column++) {
                current = max(current + get_column(column, row1, row2), 0);
                best = max(best, current);
            }
            // update maximums
            topbest[row2] = max(topbest[row2], best);
            endbest[row1] = max(endbest[row1], best);
        }
    }
    // fix up our max arrays
    for (int f = 1; f < 200; f++) { // forwards pass
        topbest[f] = max(topbest[f], topbest[f - 1]);
        leftbest[f] = max(leftbest[f], leftbest[f - 1]);
    }
    for (int b = 198; b >= 0; b--) { // backwards pass
        endbest[b] = max(endbest[b], endbest[b + 1]);
        rightbest[b] = max(rightbest[b], rightbest[b + 1]);
    }
    int best_area_final = 0;
    for (int split = 0; split < 200; split++) {
        // split = 1:
        // leftbest[split-1]
        int leftarea = split == 0 ? 0 : leftbest[split - 1];
        int rightarea = split == 200 ? 0 : rightbest[split];
        int toparea = split == 0 ? 0 : topbest[split - 1];
        int endarea = split == 200 ? 0 : endbest[split];
        best_area_final =
            max({best_area_final, leftarea + rightarea, toparea + endarea});
    }
    // wowie this was... an experience
    cout << best_area_final + countup << endl;
}
