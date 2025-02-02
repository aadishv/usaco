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
struct SquareGrid {
    int size;
    vector<pair<int, int>> marked_points = {};

    void populate() {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                char cell; cin >> cell;
                if (cell == '#') {
                    marked_points.push_back(make_pair(col, row));
                }
            }
            cin.ignore();
        }
    }

    vector<SquareGrid> getAllValidShifts(const set<pair<int, int>>& valid_positions) {
        int max_left_shift = (*min_element(all(marked_points), [](const auto& a, const auto& b) {
            return a.first < b.first;
        })).first;

        int max_right_shift = size - (*min_element(all(marked_points), [](const auto& a, const auto& b) {
            return a.first > b.first;
        })).first;

        int max_up_shift = (*min_element(all(marked_points), [](const auto& a, const auto& b) {
            return a.second < b.second;
        })).second;

        int max_down_shift = size - (*min_element(all(marked_points), [](const auto& a, const auto& b) {
            return a.second > b.second;
        })).second;

        vector<SquareGrid> valid_grids;
        for (auto x_offset = -max_left_shift; x_offset < max_right_shift; x_offset++) {
            for (auto y_offset = -max_up_shift; y_offset < max_down_shift; y_offset++) {
                auto shifted_grid = SquareGrid { size, marked_points };
                bool is_valid = true;

                for (auto& point : shifted_grid.marked_points) {
                    point = make_pair(point.first + x_offset, point.second + y_offset);
                    if (!valid_positions.count(point)) {
                        is_valid = false;
                        break;
                    }
                }

                if (is_valid) {
                    valid_grids.push_back(shifted_grid);
                }
            }
        }
        return valid_grids;
    }
};
int main() {
    // USACO 2016 US Open Contest, Bronze
    // Problem 2. Bull in a China Shop
    // https://usaco.org/index.php?page=viewproblem2&cpid=640
    // no ai help needed for a very hard problem! nice
    setIO("bcs", false);
    int gridSize = nxt(), numPieces = nxt();
    auto targetGrid = SquareGrid { gridSize };
    targetGrid.populate();
    set<pair<int, int>> targetPoints(all(targetGrid.marked_points));
    vector<SquareGrid> pieceGrids(numPieces);
    vector<vector<SquareGrid>> validShifts;
    for (auto& grid: pieceGrids) {
        grid = SquareGrid { gridSize };
        grid.populate();
        validShifts.push_back(grid.getAllValidShifts(targetPoints));
    }
    for (int piece1 = 0; piece1 < numPieces-1; piece1++) {
        for (int piece2 = piece1+1; piece2 < numPieces; piece2++) {
            for (auto shift1: validShifts[piece1]) {
                for (auto shift2: validShifts[piece2]) {
                    set<pair<int, int>> combinedPoints(all(shift1.marked_points));
                    for (auto point: shift2.marked_points) {
                        combinedPoints.insert(point);
                    };
                    if (combinedPoints == targetPoints) {
                        cout << piece1 + 1 << " " << piece2 + 1 << endl;
                        return 0;
                    }

                }
            }
        }
    }
    return 0;
}
