#include <bits/stdc++.h>
#define vi vector<int>
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
    #ifndef AADISHV
    string name = "";
    if (name.size() > 0) {
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
    #endif
}
