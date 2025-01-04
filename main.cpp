#include <bits/stdc++.h>
#include <cmath>
#define ITER(v) v.begin(), v.end()
using namespace std;

void setIO(string name = ""){
    if (name.size() > 0){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}
int main() {
    long long q;
    cin >> q;
    map<long long, long long> store;
    for (long long i = 0; i < q; i++) {
        long long op, a;
        cin >> op >> a;
        if (op == 0) {
            long long v;
            cin >> v;
            store[a] = v;
        } else if (op == 1) {
            if (store.count(a)) {
                cout << store[a] << endl;
            } else {
                cout << 0 << endl;
            }
        }
    }
    cout << endl;
    return 0;
}
