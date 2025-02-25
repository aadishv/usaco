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
    // USACO 2018 US Open Contest, Bronze
    // Problem 1. Team Tic Tac Toe
    // https://usaco.org/index.php?page=viewproblem2&cpid=831
    setIO("tttt", false);
    vector<char> board(9);
    for (int i = 0; i < 3; i++) {
        cin >> board[i*3] >> board[i*3+1] >> board[i*3+2];
        cin.ignore();
    }
    vector<vector<int>> winningLines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // horizontal straights
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // vertical straights
        {0, 4, 8}, {2, 4, 6} // diagonals;
    };
    int singleWins = 0;
    int teamWins = 0;
    for (int player1 = 'A'; player1 <= 'Z'; player1++) {
        bool hasWon = false;
        for (const auto& line : winningLines) {
            set<int> symbols = {};
            for (auto pos : line) { symbols.insert(board[pos]); };
            if (symbols.size() == 1 && symbols.count(player1)) {
                hasWon = true;
                break;
            }
        }
        singleWins += hasWon;
        if (player1 == 'Z') break;

        for (int player2 = player1+1; player2 <= 'Z'; player2++) {
            bool hasTeamWon = false;
            for (const auto& line : winningLines) {
                set<int> symbols = {};
                for (auto pos : line) { symbols.insert(board[pos]); };
                if (symbols.size() == 2 && symbols.count(player1) && symbols.count(player2)) {
                    hasTeamWon = true;
                    break;
                }
            }
            teamWins += hasTeamWon;
        }
    }
    cout << singleWins << endl << teamWins << endl;
    return 0;
}
