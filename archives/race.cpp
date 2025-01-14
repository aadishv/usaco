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
bool contains(vi v, int a) {
    set<int> vv(all(v));
    return vv.count(a);
}
int main() {
    setIO("race", true);

    unsigned long long distance, n;
    cin >> distance >> n;
    vector<unsigned long long> finish_speeds(n);
    for (unsigned long long i = 0; i < n; i++) { cin >> finish_speeds[i]; }
    string buff = "";
    printv(finish_speeds);
    for (auto finish_speed: finish_speeds) {
        // cerr << "speed" << finish_speed << endl;
        unsigned long long front = 1;
        unsigned long long back = finish_speed;
        unsigned long long fv = front; unsigned long long bv = back;
        unsigned long long t = 1;

        while (fv != finish_speed && !(front >= distance)) {
            front += ++fv;
            t++;
            if (finish_speed == 5) {
                cerr << fv << " " << front << " " << t << "|";
            }
        }
        if (finish_speed == 5) {
            cerr << "---" << endl;
            cerr << front + back << " " << t << endl;
        }
        if (!(front >= distance)) {
            t++;
            while (!(front+back >= distance) && !(front+back+fv >= distance)) {
                front += ++fv;
                back += ++bv;
                t += 2;
            }
            if (!(front + back >= distance)) t++;
        }
        buff += to_string(t) + "\n";
    }
    cout << buff;
    return 0;
}
