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
// Helper function to find index of string in vector
optional<size_t> find_index(const vector<string>& vec, const string& val) {
    auto it = find(vec.begin(), vec.end(), val);
    if (it != vec.end()) {
        return distance(vec.begin(), it);
    }
    return nullopt;
}

int check_relationship(const vector<pair<string, string>>& family_tree, string descendant, string ancestor) {
    auto print_relationship = [=](string relation) {
        cout << ancestor << " is the " << relation << " of " << descendant << endl;
    };

    // Check if they are siblings
    string mother_of_descendant, mother_of_ancestor;
    for (const auto& [mother, child] : family_tree) {
        if (child == descendant) mother_of_descendant = mother;
        if (child == ancestor) mother_of_ancestor = mother;
    }
    if (mother_of_descendant == mother_of_ancestor) {
        cout << "SIBLINGS" << endl;
        return 0;
    }

    // Traverse up family tree through direct lineage
    string current = descendant;
    vector<string> relation_names = {"mother", "grand-mother"};

    for (int generations = 1; generations < 1000; generations++) {
        string previous = current;

        // Find parent of current person
        for (const auto& [mother, child] : family_tree) {
            if (child == current) {
                current = mother;
                break;
            }
        }

        // Check if ancestor is direct ancestor
        if (current == ancestor) {
            if (generations < 2) {
                print_relationship(relation_names[generations-1]);
            } else {
                string relation = relation_names[1];
                for (int i = 0; i < generations - 2; i++) {
                    relation = "great-" + relation;
                }
                print_relationship(relation);
            }
            return 0;
        }

        // Check for aunt relationship
        for (const auto& relation : family_tree) {
            if (relation == make_pair(current, ancestor)) {
                string relation_type = "aunt";
                if (generations > 2) {
                    for (int i = 0; i < generations - 2; i++) {
                        relation_type = "great-" + relation_type;
                    }
                }
                print_relationship(relation_type);
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    // USACO 2018 US Open Contest, Bronze
    // Problem 3. Family Tree
    // https://usaco.org/index.php?page=viewproblem2&cpid=833
    setIO("family", false);

    int num_relationships;
    string younger, older;
    cin >> num_relationships >> younger >> older;

    vector<pair<string, string>> family_tree;
    for (int i = 0; i < num_relationships; i++) {
        string mother, child;
        cin >> mother >> child;
        family_tree.push_back(make_pair(mother, child));
    }

    int result = check_relationship(family_tree, younger, older);
    if (result) {
        result = check_relationship(family_tree, older, younger);
        if (!result) return 0;
    } else return 0;

    // Check if they share any common ancestors
    vector<string> ancestors = {younger};
    for (int i = 0; ++i < 1000; ) {
        auto prev_size = ancestors.size();
        for (const auto& relation : family_tree) {
            if (relation.second == ancestors.back())
                ancestors.push_back(relation.first);
        }
        if (ancestors.size() == prev_size) break;
    }

    for (int i = 0; ++i < 1000; ) {
        for (const auto& relation : family_tree) {
            if (relation.second == older) {
                older = relation.first;
            }
        }
        if (find_index(ancestors, older).has_value()) {
            cout << "COUSINS" << endl;
            return 0;
        }
    }

    cout << "NOT RELATED" << endl;
    return 0;
}
