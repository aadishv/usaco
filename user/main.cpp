#include <bits/stdc++.h>
using namespace std;
int nxt() {
    int v;
    cin >> v;
    return v;
}
struct Stretch {
    int v;
    int n;
};

deque<Stretch> parse(int n) {
    deque<Stretch> stretches = {};
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        int v = c == '0' ? 0 : 1;
        if (stretches.size() == 0 || stretches.back().v != v) {
            stretches.push_back({v, 1});
        } else {
            stretches.back().n += 1;
        }
    }
    return stretches;
}
void dbg(deque<Stretch> stretches) {
    for (auto s : stretches) {
        cout << s.n << " of " << s.v << ", ";
    }
    cout << endl;
}


bool test() {
    int n = nxt(), m = nxt();
    if (n < m)
        return false;
    auto in = parse(n);
    auto out = parse(m);
    auto p = in.begin() - 1;
    for (auto segment: out) {
        if (segment.v == 1) {
            while (p != in.begin() - 1 && !(p->v == 1 && p->n >= segment.n)) {
                p++; if (p == in.end()) return false;
            }
            // cout << "1 " << p - in.begin() << endl;
        } else if (segment.v == 0) {
            int amount = 0;
            while (amount < segment.n) {
                p++; if (p == in.end()) return false;
                amount += p->v == 0 ? p->n : 0;
            }
            cout << "0 " << p - in.begin() << endl;
        }
    }
    return true;
}

int main() {
    int n = nxt();
    for (int i = 0; i < n; i++) {
        cout << (test() ? "yes" : "no") << endl;
    }
    return 0;
}
