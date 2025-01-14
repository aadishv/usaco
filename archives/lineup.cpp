#include <bits/stdc++.h>
#include <functional>
#include <ostream>
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
    setIO("lineup", false);
    vector<string> things = {"Beatrice", "Belinda", "Bella", "Bessie", "Betsy", "Blue", "Buttercup", "Sue"};
    vi things2 = {0,1,2,3,4,5,6,7};
    vector<pair<int, int>> options = {};
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        auto ss = split(s, ' ');
        printv(ss);
        options.push_back(make_pair(
            index(things, ss.front()).value(),
            index(things, ss.back()).value()
        ));
    }
    do {
        bool good = true;
        for (auto p: options) {
            if (
                abs(
                    index(things2, p.first).value() -
                    index(things2, p.second).value()
                ) != 1) {
                good = false;
            }
            if (!good) break;
        }
        if (good) {
            for (int i: things2) {
                cout << things[i] << endl;
            }
            break;
        }
    } while (next_permutation(all(things2)));
    return 0;
}
