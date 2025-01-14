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
int check(vector<pair<string, string>> relationships, string young, string old) {
    auto print_ans = [=](string r) {
        cout << old << " is the " << r << " of " << young << endl;
    };
    // check if are siblings
    string mothera, motherb;
    for (auto relation: relationships) {
        if (relation.second == young) mothera = relation.first;
        if (relation.second == old) motherb = relation.first;
    }
    if (mothera == motherb) {
        cout << "SIBLINGS" << endl; return 0;
    }
    // go up through young's direct parents. also check direct parent's other children to see if old is in it
    string direct_relative = young;
    vector<string> direct_names = {"mother", "grand-mother"};
    for (int i = 1; i < 1000; i++) {
        auto old_direct = direct_relative;
        for (auto relation: relationships) {
            if (relation.second == direct_relative) {
                direct_relative = relation.first;
                break;
            }
        }
        // old is direct ancestor
        if (direct_relative == old) {
            // handle printing if old is direct ancestor of young
            if (i < 2) {
                print_ans(direct_names[i-1]);
            } else {
                string s = direct_names[1];
                for (int j = 0; j < i - 2; j++) { s = "great-" + s; };
                print_ans(s);
            }
            // cerr << "returning";
            return 0;
        }
        // check parent
        for (auto relation: relationships) {
            if (relation == make_pair(direct_relative, old)) {
                // aunt = 2, great-aunt = 3
                string s = "aunt";
                if (i > 2) {
                    for (int j = 0; j < i - 2; j++) {
                        s = "great-" + s;
                    }
                }
                print_ans(s);
                // cerr << "returning2";
                return 0;
            }
        }
    }
    return 1;
}
int main() {
    setIO("family", false);

    int nnn; string young, old;
    cin >> nnn >> young >> old;
    vector<pair<string, string>> relationships = {}; // first is mother of second
    for (int i = 0; i < nnn; i++) {
        string a, b; cin >> a >> b;
        relationships.push_back(make_pair(a, b));
    }
    int result = check(relationships, young, old);
    if (result) {
        result = check(relationships, old, young);
        if (!result) return 0;
    } else return 0;
    // check if they share a common ancestor at all
    // bfs <<< just check the lists of parents dumbo lol
    // cout << "RUN";
    vector<string> na = {young};
    for (int i = 0; ++i < 1000; ) {
        auto len = na.size();
        for (auto r: relationships) {
            if (r.second == na.back()) na.push_back(r.first);
        }
        if (na.size() == len) break;
    }
    for (int i = 0; ++i < 1000; ) {
        for (auto r: relationships) {
            if (r.second == old) {
                old = r.first;
            }
        }
        if (index(na, old).has_value()) {
            cout << "COUSINS" << endl;
            return 0;
        }
    }
    cout << "NOT RELATED" << endl;
    return 0;
}
