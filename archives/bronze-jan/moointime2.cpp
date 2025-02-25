#include <bits/stdc++.h>
#define vi vector<int>
#define ll long long
#define all(i) i.begin(), i.end()
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

ll nxt() {ll a; cin >> a; return a;}

int main() {
    // USACO 2025 January Contest, Bronze
    // Problem 2. It's Mooin' Time II
    // https://usaco.org/index.php?page=viewproblem2&cpid=1468
    ll sequenceLength = nxt();
    map<ll, set<ll>> numberPositions = {};
    set<ll> uniqueNumbers = {};
    vector<ll> uniqueCountHistory = {0};
    int currentPosition = 0;

    vector<ll> numbers(sequenceLength);
    for (auto& num: numbers) {
        num = nxt();
        uniqueNumbers.insert(num);
        numberPositions[num].insert(currentPosition);
        uniqueCountHistory.push_back(uniqueNumbers.size());
        currentPosition++;
    }

    ll result = 0;
    for (auto numberOccurrence: numberPositions) {
        auto occurrenceCount = numberOccurrence.second.size();
        if (occurrenceCount >= 2) {
            set<ll>::iterator secondLastPos = numberOccurrence.second.end();
            advance(secondLastPos, -2);
            result += uniqueCountHistory[*secondLastPos] - (occurrenceCount > 2);
        }
    }
    cout << result << endl;
}
// 808608712
