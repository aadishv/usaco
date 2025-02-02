#include <bits/stdc++.h>
#define vi vector<int>
#define ll long long
#define all(i) i.begin(), i.end()
#define cast static_cast
#define DEBUG_MODE true

using namespace std;

template<typename T>
void dbg(vector<T> vs, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    for (auto v: vs) cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}
template<typename T>
void dbg(T v, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}

int nxt() {int a; cin >> a; return a;}

int main() {
    // cow checkups
    int n = nxt();
    vi current(n); for (auto& i: current) i = nxt();
    vi expected(n); for (auto& i: expected) i = nxt();
    int total = 0;
    for (int i = 0; i < n; i++) total += current[i] == expected[i];
    map<int, int> options = {};
    for (int center = 1; center < n-1; center++) {
        int change = total;
        for (int radius = 1; radius <= min(center-0, n-center-1); radius++) {
            // start = center-radius, end = center+radius (include end!)
            change -= current[center-radius] == expected[center-radius];
            change -= current[center+radius] == expected[center+radius];
            change += current[center+radius] == expected[center-radius];
            change += current[center-radius] == expected[center+radius];
            options[change]++;
        }
    }
    options[total] += n;
    for (int center = 0; center < n-1; center++) {
        // the REAL center is center+0.5 (e.g. 0 -> 0.5)
        int change = total;
        // cout << n-center-1 << " " << center+1 << endl;
        for (int radius = 1; radius <= min(center+1, n-center-1); radius++) {
            // cout << center+1-radius << " " << center+radius << endl;
            change -= current[center-radius+1] == expected[center-radius+1];
            change -= current[center+radius] == expected[center+radius];
            change += current[center+radius] == expected[center-radius+1];
            change += current[center-radius+1] == expected[center+radius];
            options[change]++;
        }
    }
    for (int t = 0; t <= n; t++) {
        cout << options[t] << endl;
    }
}
/*
65168
236542
118739
50421
19458
7231
1851
804
*/
