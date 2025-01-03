#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
vector<int> neighs(int p) {
    vector<int> offsets = {-1, 1, 10, -10};
    vector<int> result = {};
    for (int offset : offsets) {
        int neigh = offset + p;
        if (neigh < 100 && neigh > 0) {
            result.push_back(neigh);
        }
    }
    return result;
}

int manhattan_distance(int a, int b) {
    return abs( (a % 10) - (b % 10) ) + abs( int(a / 10) - int(b / 10) );

}
int main() {
    // cout << "running" << endl;
    setIO("buckets");
    char p;
    int pos = 0;
    int offsets[4] {-1, 1, 10, -1};
    int b;
    int r;
    int l;
    for (int i = 0; i < 100; i++) {
        cin >> p;
        if (p == 'L') {
            l = pos;
        }
        else if (p == 'R') {
            r = pos;
        }
        else if (p == 'B') {
            b = pos;
        }
        pos++;
    }
    int dist = manhattan_distance(b, l);
    bool flag = false;
    if (b/10 == l/10 && l/10 == r/10) {
        if ( ((r > l) && (r < b)) || ((r < l) && (r > b)) ) {
            flag = true;
        }
    }
    if (b%10 == l%10 && l%10 == r%10) {
        if ( ((r > l) && (r < b)) || ((r < l) && (r > b)) ) {
            flag = true;
        }
    }

    if (flag) {
        dist += 2; // to go around R; when they are aligned is the only weird case
    }
    cout << dist - 1;
    return 0;
}
