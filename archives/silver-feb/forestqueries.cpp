#include <bits/stdc++.h>
#define vi vector<int>
// #define all(it) it.begin(), it.end()
// #define ball(it) it.begin(), it.begin()
// #define ll long long
// #define cast(a, b) static_cast<b>(a)
using namespace std;
namespace utils {
    int nxt() {int a; cin >> a; return a;};
    template<typename T>
    T gnxt() {T a; cin >> a; return a;}
    template<typename T>
    void dbgv(vector<T> vs, string id = "") {
        if (id != "") cerr << id << ":\t";
        for (auto v: vs) cerr << v << " ";
        cerr << endl;
    }
    // void dbg() { cerr << endl; }  // base case
    // template<typename T, typename... Args>
    // void dbg(T a, Args... args) {
    //     cerr << a << " ";
    //     dbg(args...);
    // }
}
using namespace utils;

int main() {
    // CSES Problem Set
    // Forest Queries
    // https://cses.fi/problemset/task/1652
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int gridSize = nxt(), numQueries = nxt();
    int prefixSum[1001][1001]{{0}}; // prefixSum[row+1][col+1]
    for (int row = 0; row < gridSize; row++) {
        auto inputLine = gnxt<string>();
        for (int col = 0; col < gridSize; col++) {
            prefixSum[row+1][col+1] =
                prefixSum[row+1][col] + prefixSum[row][col+1] - prefixSum[row][col] + (inputLine[col] == '*');
        }
        cin.ignore(1);
    }
    stringstream output;
    while (numQueries--) {
        int startRow, startCol, endRow, endCol;
        cin >> startRow >> startCol >> endRow >> endCol;
        output << prefixSum[endRow][endCol]
                - prefixSum[endRow][startCol-1]
                - prefixSum[startRow-1][endCol]
                + prefixSum[startRow-1][startCol-1]
            << '\n';
    }
    cout << output.str() << endl;
}
