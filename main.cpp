#include <bits/stdc++.h>
#define vi vector<int>
#define all(a) a.begin(), a.end()
using namespace std;

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
int nxt() {
    int a; cin >> a; return a;
}
template<typename T>
void printv(vector<T> v) {
    for (unsigned long long i = 0; i < v.size(); i++) {
        cerr << v[i] << " ";
    }
    cerr << endl;
}
template<typename T>
optional<int> index(vector<T> v, T a) {
    auto p = v.begin();
    while (*p != a && p != v.end()) p++;
    if (p == v.end()) return nullopt;
    return p-v.begin();
}
vector<string> split(string s, char sep) {
    vector<string> result = {};
    string cur = "";
    auto p = s.begin();
    while (p != s.end()) {
        if (*p == sep) {
            result.push_back(cur);
            cur = "";
        }
        else
            cur.push_back(*p);
        p++;
    }
    result.push_back(cur);
    return result;
}
int main() {
    setIO("", false);

    return 0;
}
