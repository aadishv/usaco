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
int main() {
    int n;
    cin >> n;
    vector<Cow> cows = {};
    vector<Collision> collisions = {};
    vector<int> deaths(n, -1);
    for (int i = 0; i < n; i++) {
        char dir;
        int x, y;
        cin >> dir >> x >> y;
        Cow cow { x, y, i, dir };
        cows.push_back(cow);
    }
    for (auto ncow: cows) {
        if (ncow.dir == 'E') {
            continue;
        }
        for (auto ecow: cows) {
            if (ecow.dir == 'N') {
                continue;
            }
            if (ncow.x > ecow.x && ecow.y > ncow.y) {
                // there is a possibility of a collision
                int cx = ncow.x;
                int cy = ecow.y;
                int ndist = abs(ncow.y - cy);
                int edist = abs(ecow.x - cx);
                collisions.push_back(Collision { ncow, ecow, cx, cy, ndist, edist });
            }
        }
    }
    sort(collisions.begin(), collisions.end(), [](const Collision &a, const Collision &b) {
        return min(a.ndist, a.edist) < min(b.ndist, b.edist);
    });
    for (auto collision: collisions) { // NOTE: This is a POSSIBLE COLLISION
        bool egood = deaths[collision.ecow.ind]>collision.edist || deaths[collision.ecow.ind] == -1; // will be true for -1
        bool ngood = deaths[collision.ncow.ind]>collision.ndist || deaths[collision.ncow.ind] == -1; // will be true for -1

        if (egood && ngood) { // both are still alive
            if (collision.edist < collision.ndist) { // ecow will reach collision point first and continue, n dies
                deaths[collision.ncow.ind] = collision.ndist;
            } else if (collision.ndist < collision.edist) { // and vice versa
                deaths[collision.ecow.ind] = collision.edist;
            }
        }
    }
    for (int death: deaths) {
        cout << ((death == -1) ? "Infinity" : to_string(death)) << endl;
    }

    /*
    1. find all collisions
    2. sort collisions by what time the cow stops
    3. go through each collission, check if still possible based on death time,
       and update death time for that cow
    */

    return 0;
}
