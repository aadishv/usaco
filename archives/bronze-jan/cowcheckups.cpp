#include <bits/stdc++.h>
#define vi vector<int>
#define ll long long
#define all(i) i.begin(), i.end()
#define cast static_cast
#define DEBUG_MODE true

using namespace std;

template<typename T>
void dbg(vector<T> vs, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    for (auto v: vs) cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}
template<typename T>
void dbg(T v, string id = "") {
    #if DEBUG_MODE
    if (id != "") cout << id << ":\t";
    cout << v << " ";
    cout << endl;
    #else
    return;
    #endif
}

int nxt() {int a; cin >> a; return a;}

int main() {
    // USACO 2025 January Contest, Bronze
    // Problem 3. Cow Checkups
    // https://usaco.org/index.php?page=viewproblem2&cpid=1469
    int n = nxt();
    vi currentOrdering(n); for (auto& i: currentOrdering) i = nxt();
    vi expectedOrdering(n); for (auto& i: expectedOrdering) i = nxt();

    int matchCount = 0;
    for (int i = 0; i < n; i++) matchCount += currentOrdering[i] == expectedOrdering[i];

    map<int, int> matchesAfterSwap = {};

    // Handle full integer positions as centers
    for (int centerPos = 1; centerPos < n-1; centerPos++) {
        int newMatchCount = matchCount;
        for (int swapDistance = 1; swapDistance <= min(centerPos-0, n-centerPos-1); swapDistance++) {
            // Remove matches that will be broken
            newMatchCount -= currentOrdering[centerPos-swapDistance] == expectedOrdering[centerPos-swapDistance];
            newMatchCount -= currentOrdering[centerPos+swapDistance] == expectedOrdering[centerPos+swapDistance];
            // Add new matches after swap
            newMatchCount += currentOrdering[centerPos+swapDistance] == expectedOrdering[centerPos-swapDistance];
            newMatchCount += currentOrdering[centerPos-swapDistance] == expectedOrdering[centerPos+swapDistance];
            matchesAfterSwap[newMatchCount]++;
        }
    }

    matchesAfterSwap[matchCount] += n;

    // Handle half positions as centers (e.g. 0.5, 1.5, etc)
    for (int centerPos = 0; centerPos < n-1; centerPos++) {
        int newMatchCount = matchCount;
        for (int swapDistance = 1; swapDistance <= min(centerPos+1, n-centerPos-1); swapDistance++) {
            // Remove matches that will be broken
            newMatchCount -= currentOrdering[centerPos-swapDistance+1] == expectedOrdering[centerPos-swapDistance+1];
            newMatchCount -= currentOrdering[centerPos+swapDistance] == expectedOrdering[centerPos+swapDistance];
            // Add new matches after swap
            newMatchCount += currentOrdering[centerPos+swapDistance] == expectedOrdering[centerPos-swapDistance+1];
            newMatchCount += currentOrdering[centerPos-swapDistance+1] == expectedOrdering[centerPos+swapDistance];
            matchesAfterSwap[newMatchCount]++;
        }
    }

    for (int matches = 0; matches <= n; matches++) {
        cout << matchesAfterSwap[matches] << endl;
    }
}
/*
65168
236542
118739
50421
19458
7231
1851
804
*/
