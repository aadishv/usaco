#include <bits/stdc++.h>

#define ITER(v) v.begin(), v.end()
#define vi vector<int>
using namespace std;

// void setIO(string name = ""){
//     if (name.size() > 0){
//         freopen((name+".in").c_str(), "r", stdin);
//         freopen((name+".out").c_str(), "w", stdout);
//     }
// }
bool is_nice(vector<int> arr) {
    vi a = arr;
    set<int> seen = {};
    auto p = a.begin();
    while (p != a.end()) {
        if (seen.count(*p)) {
            return false;
        }
        int v = *p;
        while (p != a.end() && *p == v) p++;
        seen.insert(v);
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    cin.ignore(2);
    map<int, int> freq;
    vi arr(n);
    for (auto& a: arr) {cin >> a; freq[a]++;};
    int d = 0;
    while (!is_nice(arr)) {
        set<int> s(arr.begin(), arr.end());
        int v = *min_element(s.begin(), s.end(), [&](const int a, const int b) {
            return freq[a] > freq[b];
        });
        auto f = arr.begin();
        auto l = arr.end()-1;
        while (*f != v) f++;
        while (*f != v) l--;
        s = set<int>(f, ++l);
        for (auto& e: arr) {
            if (s.count(e) && e != v) {
                e = v;
                freq[e]--;
                freq[v]++;
                d++;
            }
        }
    }
    cout << d << "\n";
    return 0;
}
