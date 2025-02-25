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
    // USACO 2016 December Contest, Bronze
    // Problem 3. The Cow-Signal
    // https://usaco.org/index.php?page=viewproblem2&cpid=665
    setIO("cowsignal", false);
    int height, width, scale;
    cin >> height >> width >> scale;
    for (int row = 0; row < height; row++) {
        string signal_line;
        cin >> signal_line;
        for (int repeat_row = 0; repeat_row < scale; repeat_row++) {
            for (char signal_char : signal_line) {
                for (int repeat_char = 0; repeat_char < scale; repeat_char++) {
                    cout << signal_char;
                }
            }
            cout << endl;
        }
    }
    return 0;
}
