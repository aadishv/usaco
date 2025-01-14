#include <bits/stdc++.h>
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
    for (unsigned long i = 0; i < v.size(); i++) {
        // cout << v[i] << " ";
    }
    // cout << endl;
}
bool contains(vi v, int a) {
    set<int> vv(all(v));
    return vv.count(a);
}
bool check_good_cows(vi cows, vi order) {
    auto order_pointer = order.begin();
    int local_free_spaces = 0;
    auto last_order_pointer = order.begin();
    for (auto c: cows) {
        if (c == -1) local_free_spaces++;
        if (contains(order, c)) {
            while (*order_pointer != c && order_pointer != order.end())
                order_pointer++;
            if (order_pointer == order.end()) return false;
            if (order_pointer - last_order_pointer > local_free_spaces)
                return false;
            local_free_spaces = 1;
            last_order_pointer = order_pointer;
        }
    }
    return true;
}
int main() {
    setIO("milkorder");
    int num_cows = nxt();
    vi cows(num_cows, -1);
    vi order(nxt());
    int num_set = nxt();

    for (int i = 0; i < order.size(); i++) { int c = nxt(); order[i] = c; }
    cin.ignore();
    for (int i = 0; i < num_set; i++) {
        int c = nxt();
        if (c == 1) return 0;
        cows[nxt()-1] = c;
        cin.ignore();
    }

    for (int possible_position = 0; possible_position < cows.size(); possible_position++) {
        if (cows[possible_position] == -1) {
            vi newc = cows;
            newc[possible_position] = 1;
            if (check_good_cows(newc, order)) {
                cout << possible_position + 1 << endl;
                return 0;
            }
        }
    }
}

// 3 4 5 6 1 _
