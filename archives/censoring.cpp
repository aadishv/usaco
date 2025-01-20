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
    // USACO 2015 February Contest, Bronze
    // Problem 1. Censoring (Bronze)
    // https://usaco.org/index.php?page=viewproblem2&cpid=526
    setIO("censor", false);
    string inputText; cin >> inputText;
    string wordToCensor; cin >> wordToCensor;
    string resultText = "";
    auto currentChar = inputText.begin();

    while (currentChar != inputText.end()) {
        resultText += *currentChar;
        int matchStartPos = resultText.size() - wordToCensor.size();

        if (matchStartPos >= 0) {
            if (resultText.substr(matchStartPos) == wordToCensor) {
                resultText.erase(matchStartPos);
            }
        }
        currentChar++;
    }

    cout << resultText << endl;
    return 0;
}
