#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define rall(it) it.rbegin(), it.rend()
#define ll long long
#define cast(a, b) static_cast<b>(a)
using namespace std;
int nxt() {int a; cin >> a; return a;};

template<typename T>
void dbg(vector<T> vs, string id = "") {
    if (id != "") cerr << id << ":\t";
    for (auto v: vs) cerr << v << " ";
    cerr << endl;
}
template<typename T>
void dbg(T v, string id = "") {
    if (id != "") cerr << id << ":\t";
    cerr << v << " ";
    cerr << endl;
}

// **Do not remember this function** for contests
void setIO(string name = "") {
    #ifndef AADISHV
    if (name.size() > 0){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
    #endif
}
bool wins(char j, char b) {
    return (b == 'H' && j == 'S') || (b == 'S' && j == 'P') || (b == 'P' && j == 'H');
}
int main() {
    // USACO 2017 January Contest, Silver
    // Problem 2. Hoof, Paper, Scissors
    // https://usaco.org/index.php?page=viewproblem2&cpid=691
    setIO("hps");
    int numMoves = nxt();
    vector<char> johnMoves(numMoves);
    map<char, vi> winsPrefix = {};
    map<char, vi> rwinsPrefix = {};
    string moveTypes = "HPS";
    for (auto moveType: moveTypes) { vi sum(numMoves+1, 0); winsPrefix[moveType] = sum; }
    for (auto moveType: moveTypes) { vi sum(numMoves+1, 0); rwinsPrefix[moveType] = sum; }
    for (int i = 0; i < numMoves; i++) {
        char johnMove; cin >> johnMove;
        johnMoves[i] = johnMove;
        for (auto c: moveTypes) {
            winsPrefix[c][i+1] = wins(johnMove, c) + winsPrefix[c][i];
        }
    }
    for (int i = numMoves-1; i >= 0; i--) {
        for (auto c: moveTypes) {
            rwinsPrefix[c][i] = rwinsPrefix[c][i+1] + wins(johnMoves[i], c);
        }
    }
    int maxWins = 0;
    for (char firstStrategy: moveTypes) {
        vi firstStrategyWins = winsPrefix[firstStrategy];
        for (char secondStrategy: moveTypes) {
            // int secondStrategyWins = winsPrefix[secondStrategy].back();
            vi secondStrategyWins = rwinsPrefix[secondStrategy];
            for (int splitPoint = 0; splitPoint < numMoves; splitPoint++) {
                maxWins = max(maxWins, /*secondStrategyWins*/ secondStrategyWins[splitPoint] + firstStrategyWins[splitPoint]);
                // secondStrategyWins -= wins(johnMoves[splitPoint], secondStrategy);
            }
        }
    }
    cout << maxWins << endl;
    return 0;
}
