#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
#define cast static_cast
#define DEBUG_MODE false
using namespace std;
int nxt() {int a; cin >> a; return a;};

template<typename T>
void dbg(vector<T> vs, string id = "") {
    #if DEBUG_MODE
    if (false) return;
    if (id != "") {
        cout << id << "\t";
    }
    for (auto v: vs) cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}

// **Do not remember this function** for contests
void setIO(string name = "", bool maxio = false) {
    if (name.size() > 0){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
    if (maxio) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
    }
}

int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    setIO("", false);

    return 0;
}
