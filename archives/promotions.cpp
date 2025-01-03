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
    setIO("promote");
    int b1, b2, s1, s2, g1, g2, p1, p2;
    cin >> b1 >> b2 >> s1 >> s2 >> g1 >> g2 >> p1 >> p2;
    int num_gained_p = p2 - p1;
    int num_gained_g = g2 - g1 + num_gained_p;
    int num_gained_s = s2 - s1 + num_gained_g;
    cout << num_gained_s << endl << num_gained_g << endl << num_gained_p;
    return 0;
}
