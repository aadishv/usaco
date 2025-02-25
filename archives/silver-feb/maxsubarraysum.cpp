#include <bits/stdc++.h>
#define vi vector<ll>
#define all(it) it.begin(), it.end()
#define ball(it) it.begin(), it.begin()
#define ll long long
#define cast(a, b) static_cast<b>(a)
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
    void dbg() { cerr << endl; }  // base case
    template<typename T, typename... Args>
    void dbg(T a, Args... args) {
        cerr << a << " ";
        dbg(args...);
    }
}
using namespace utils;

int main() {
    // CSES Problem Set
    // Maximum Subarray Sum
    // https://cses.fi/problemset/task/1643
    ll length = gnxt<ll>();
    ll maxSum = 0;
    ll minPrefix = 0;
    ll currentSum = 0;
    for (ll i = 0; i < length; i++) {
        ll newSum = currentSum + gnxt<ll>();
        if (i == 0) {
            maxSum = newSum;
        }
        ll possibleMax = newSum - minPrefix;
        maxSum = max(maxSum, possibleMax);
        currentSum = newSum;
        minPrefix = min(newSum, minPrefix);
    }
    cout << maxSum << endl;
    return 0;
}
