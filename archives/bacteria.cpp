#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
using namespace std;
int nxt() {int a; cin >> a; return a;};

template<typename T>
void dbg(vector<T> vs, string id = "") {
    if (false) return;
    if (id != "") {
        cout << id << "\t";
    }
    for (auto v: vs) cout << v << " ";
    cout << endl;
}

int main() {
    // USACO 2024 January Contest, Bronze
    // Problem 3. Balancing Bacteria
    // https://usaco.org/index.php?page=viewproblem2&cpid=1373
    ll nareas; cin >> nareas;
    vector<ll> areas(nareas); for (auto& a : areas) cin >> a;
    vector<ll> offsets(nareas, 0);
    long long total = 0;
    for (long long i = 0; i < nareas - 1; i++) {
        // MARK: - naiive approach
        /* works pretty well but fails on test cases 10-15 due to timeout
        NOTE: in order to test this, change the upper limit on above
        for loop to `i < nareas` (not `i < nareas-1`) and remove addition
        on the final print line

        it's kinda funny that I found this approach only after working on the
        math for an hour -- it was good though because it was easy to
        transition to the efficient approach afterwards */

        // long long amount = -areas[i]-offsets[i];
        // for (long long p = i; p < nareas; p++) {
        //     // dbg<ll>({p, i});
        //     offsets[p] += amount*(1+p-i);
        // }
        // // dbg(areas);
        // total += abs(amount);

        // MARK: - better approach
        /* got it after half an hour or so of messing about with the maths,
        I'm sure there's a more intuitive way
        (or an intuitive explanantoion for this) */
        ll be = areas[i-1];
        if (i == 0) be = 0;
        total += abs(areas[i+1]-2*areas[i]+be);
    }
    cout << total + abs(areas[0]) << endl;
    return 0;
}
