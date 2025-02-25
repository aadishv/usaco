#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
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

int main() {
    // Codeforces Round 870 (Div. 2)
    // D. Running Miles
    // https://codeforces.com/contest/1826/problem/D
    setIO("", false);
    int testCases = nxt();
    for (int testNum = 0; testNum < testCases; testNum++) {
        int arrayLength = nxt();
        vi beautyScores(arrayLength);
        for (auto& score: beautyScores) score = nxt();

        // Maximum value of: beautyScore[m] + (beautyScore[l] + l) + (beautyScore[r] - r)
        vi maxBeautyWithLeft(arrayLength, beautyScores[0] + 1);
        vi maxBeautyWithRight(arrayLength + 1, beautyScores.back() - arrayLength);

        for (int i = 1; i < arrayLength; i++) {
            maxBeautyWithLeft[i] = max(maxBeautyWithLeft[i-1], beautyScores[i] + (i+1));
        }
        for (int i = arrayLength - 2; i >= 0; i--) {
            maxBeautyWithRight[i] = max(maxBeautyWithRight[i+1], beautyScores[i] - (i+1));
        }

        int maxBeautySum = 0;
        for (int middle = 1; middle < arrayLength-1; middle++) {
            maxBeautySum = max(maxBeautySum,
                beautyScores[middle] + maxBeautyWithLeft[middle-1] + maxBeautyWithRight[middle+1]);
        }
        cout << maxBeautySum << endl;
    }
    return 0;
}
