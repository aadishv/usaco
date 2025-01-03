#include <bits/stdc++.h>
using namespace std;

void setIO(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}
struct Cow {
    int x, y, ind;
    char dir;
};
struct Collision {
    Cow ncow, ecow;
    int cx, cy; // collision point
    int ndist, edist; // dist ecow/ncow travel before collission
};
bool n_in_circular_range(int n, int range_start, int range_end) {
    if (range_start <= range_end) {
        return range_start < n && n < range_end;
    } else { // OMG it's a circle
        return n > range_start || n < range_end;
    }
}
int main() {
    // setIO("cownomics");
    int n, m;
    cin >> n >> m;
    cin.ignore(1);
    vector<string> good;
    vector<string> bad;
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        good.push_back(s);
    }
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        bad.push_back(s);
    }
    int t = 0;
    for (int a = 0; a < m; a++) {
        // cout << "a" << a << endl;
        for (int b = a+1; b < m; b++) {
            // cout << "b" << b << endl;
            for (int c = b+1; c < m; c++) {
                // cout << "c" << c << endl;
                set<vector<char>> contained = {};
                for (string g: good) {
                    contained.insert({g[a], g[b], g[c]});
                }
                bool good = true;
                for (string bb: bad) {
                    vector<char> thing = {bb[a], bb[b], bb[c]};
                    if (contained.count(thing) > 0) {
                        good = false;
                        break;
                    }
                }
                t += good;
            }
        }
    }
    cout << t << endl;
    /*
    1. find all collisions
    2. sort collisions by what time the cow stops
    3. go through each collission, check if still possible based on death time,
       and update death time for that cow
    */

    return 0;
}
/*
Positions:    1 2 3 4 5 6 7 ... M

Spotty Cow 1: A A T C C C A ... T
Spotty Cow 2: G A T T G C A ... A
Spotty Cow 3: G G T C G C A ... A

Plain Cow 1:  A C T C C C A ... G
Plain Cow 2:  A G T T G C A ... T
Plain Cow 3:  A G T T C C A ... T
*/
