// echo "clear && clang++ main.cpp -std=c++17 -Wall -Wextra -O2 -lm && time ./a.out < input.txt" > ~/.runner_settings
// cp template.cpp main.cpp
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
int nxt() { int a; cin >> a; return a; }
long long llnxt() { long long a; cin >> a; return a; }

int main() {
    // USACO 2023 February Contest, Bronze
    // Problem 3. Watching Mooloo
    // https://usaco.org/index.php?page=viewproblem2&cpid=1301
    setIO("", false);
    long long ndays = llnxt(), k = llnxt();
    vector<long long> days(ndays); for (auto& d: days) d = llnxt();
    // MARK: - generate clusters
    vector<pair<long long, long long>> clusters = {make_pair(days[0], days[0])};
    // inclusive both ends
    for (auto d = days.begin()+1; d < days.end(); d++) {
        if (clusters.back().second + 1 == *d) {
            clusters.back().second = *d;
        } else {
            clusters.push_back(make_pair(*d, *d));
        }
    }
    // MARK: - optimally merge clusters
    vector<pair<long long, long long>> newc = {clusters.front()};
    for (auto pointer = clusters.begin()+1; pointer < clusters.end(); pointer++) {
        long long diff = (pointer->first)-(newc.back().second)-1;
        if (diff < k)
            newc.back().second = pointer->second;
        else
            newc.push_back(*pointer);
    }
    clusters = newc;
    // MARK: - score moonies
    long long cost = k * clusters.size();
    // for (auto cluster: clusters) {
    //     cout << cluster.first << "|" << cluster.second << endl;
    // }
    for (auto cluster: clusters) {
        cost += 1 + cluster.second - cluster.first;
    }
    cout << cost << endl;
    return 0;
}
