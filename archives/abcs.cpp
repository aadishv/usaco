#include <bits/stdc++.h>
using namespace std;

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
int nonspacechars(string s) {
    int t = 0;
    for (char c: s) {
        if (c != ' ') {
            t++;
        }
    }
    return t;
}

template <typename T>
void printv(vector<T> v) {
    for (const T &num : v) {
        cout << num << " ";
    }
    cout << endl;
}
template <typename T>
vector<T> removed(vector<T> v, T val) {
    bool flag = false;
    vector<T> result = {};
    for (T i: v) {
        if (i == val && !flag) {
            flag = true;
        } else {
            result.push_back(i);
        }
    }
    return result;
}
int main() {
    // setIO("word");
    vector<long long> ops = {0,0,0,0,0,0,0};
    cin >> ops[0] >> ops[1] >> ops[2] >> ops[3] >> ops[4] >> ops[5] >> ops[6];
    long long sumabc = *std::max_element(ops.begin(), ops.end());
    ops = removed(ops, sumabc);

    long long a = *std::min_element(ops.begin(), ops.end());
    ops = removed(ops, a);
    long long b = *std::min_element(ops.begin(), ops.end());
    ops = removed(ops, b);
    for (long long cop : ops) {
        if (a + b + cop == sumabc) {
            cout << a << " " << b << " " << cop;
            return 0;
        }
    }
    return 0;
}
