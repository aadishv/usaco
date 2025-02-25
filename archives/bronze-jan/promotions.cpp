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
    // USACO 2016 January Contest, Bronze
    // Problem 1. Promotion Counting
    // https://usaco.org/index.php?page=viewproblem2&cpid=591
    setIO("promote");
    int bronze_before, bronze_after;
    int silver_before, silver_after;
    int gold_before, gold_after;
    int platinum_before, platinum_after;

    cin >> bronze_before >> bronze_after;
    cin >> silver_before >> silver_after;
    cin >> gold_before >> gold_after;
    cin >> platinum_before >> platinum_after;

    int promotions_to_platinum = platinum_after - platinum_before;
    int promotions_to_gold = gold_after - gold_before + promotions_to_platinum;
    int promotions_to_silver = silver_after - silver_before + promotions_to_gold;

    cout << promotions_to_silver << endl;
    cout << promotions_to_gold << endl;
    cout << promotions_to_platinum;
    return 0;
}
