#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
#define cast static_cast
using namespace std;
int nxt() {int a; cin >> a; return a;};

template<typename... Args>
void dbg(const Args&... args) {
    ((cout << args), ...);
    cout << endl;
}


int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    // walking along a fence
    int ncows = nxt(), nposts = nxt();
    int ox = nxt(), oy = nxt(), x = ox, y = oy;
    vector<pair<int, int>> posts = {make_pair(ox, oy)};
    for (int p = 0; p < nposts-1; p++) {
        posts.push_back(make_pair(nxt(), nxt()));
    }; posts.push_back(make_pair(ox, oy));
    vector<pair<pair<int, int>, pair<int, int>>> queries = {};
    for (int c = 0; c < ncows; c++) {
        queries.push_back(make_pair(make_pair(nxt(), nxt()), make_pair(nxt(), nxt())));
    }
    set<pair<int, int>> needed = {};
    for (auto q: queries) { needed.insert(q.first); needed.insert(q.second); }
    map<pair<int, int>, int> distances = {{make_pair(ox, oy), 0}};
    int total = 0;
    for (auto post: posts) {
        int px = post.first, py = post.second;
        int xc = px == x ? 0 : px > x ? 1 : -1;
        int yc = py == y ? 0 : py > y ? 1 : -1;
        while (px != x || py != y) {
            x += xc; y += yc;
            total++;
            if (needed.count(make_pair(x, y))) {
                distances[make_pair(x, y)] = total;
            }
        }
    };
    // dbg(points.size());
    for (auto q: queries) {
        int d1 = abs(distances[q.first]-distances[q.second]);
        int d2 = total-d1;
        int dist = min(d1, d2);
        cout << dist << endl;
    }
    // cout << abs(find(all(points), make_pair(0,0)) - find(all(points), make_pair(2,2))) << endl;
    // cout << points.size()-abs(find(all(points), make_pair(0,0)) - find(all(points), make_pair(2,2))) << endl;
    // for (auto entry: points) cout << entry.first << "|" << entry.second << endl;
    return 0;
}
