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
int main() {
    // USACO 2016 February Contest, Bronze
    // Problem 1. Milk Pails
    // https://usaco.org/index.php?page=viewproblem2&cpid=615
    setIO("pails", false);
    int bucket1_size, bucket2_size, target_volume;
    bucket1_size = nxt(); bucket2_size = nxt(); target_volume = nxt();
    int min_remainder = INT_MAX;
    for (int bucket1_fills = 0; bucket1_fills <= target_volume/bucket1_size; bucket1_fills++) {
        int remainder = (target_volume-(bucket1_size*bucket1_fills)) % bucket2_size;
        min_remainder = min(min_remainder, remainder);
    }
    cout << target_volume - min_remainder << endl;
    return 0;
}
