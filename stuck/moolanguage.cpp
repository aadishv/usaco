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

struct PartialSentence {
    // sentence and vectors are all for show lol
    string sentence;
    int noun, trans, intras, conjunction, comma, period; // amount remaining
    bool ends_with_and;
    vector<PartialSentence> repopulate(vector<string> nouns, vector<string> transs, vector<string> intrass, vector<string> conjunctions) {
        auto self = *this;
        vector<PartialSentence> possible_sentences = {};
        // intransitive sentence
        if (noun && intras && period) {
            auto p = self;
            p.sentence += nouns[--p.noun] + " " + intrass[--p.intras] + ". ";
            p.period--;
            p.ends_with_and = false;
            possible_sentences.push_back(p);
        }
        if (period && noun>1 && trans) {
            int max_amount = min(comma+1, noun-1);
            for (int plural_count = 1; plural_count <= max_amount; plural_count++) {
                // cout << "test3" << plural_count << "|" << max_amount << endl;
                auto newone = self;
                newone.comma -= plural_count-1;
                newone.period--;
                newone.sentence += nouns[--newone.noun] + " " + transs[--newone.trans] + " ";

                for (int i = 0; i < plural_count; i++) {
                    newone.sentence += nouns[--newone.noun];
                    if (i != plural_count-1) {
                        newone.sentence += ", ";
                    }
                }
                newone.sentence += ". ";
                newone.ends_with_and = false;
                possible_sentences.push_back(newone);
            }
        }

        if (conjunction && !ends_with_and) {
            auto s = possible_sentences.size();
            for (int p = 0; p < s; p++) {
                auto other = possible_sentences[p];
                if (other.conjunction && !ends_with_and) {
                    other.ends_with_and = true;
                    other.period++;
                    other.sentence.erase(other.sentence.size()-2, other.sentence.size());
                    other.sentence += " " + conjunctions[--other.conjunction] + " ";
                    possible_sentences.push_back(other);
                }
            }
        }
        return possible_sentences;
    }
    tuple<int, int, int, int, int, int, bool> unique() {
        return make_tuple(noun, trans, intras, conjunction, comma, period, ends_with_and);
    }
};

// nhoj mooed. farmer taught elsie, bessie and john flew.
void solve_test_case() {
    vector<string> nouns = {}, transitives = {}, intransitives = {}, conjunctions = {};
    int words = nxt(), commas = nxt(), periods = nxt();
    for (int i = 0; i < words; i++) {
        string word, type;
        cin >> word >> type;
        if (type == "noun") nouns.push_back(word);
        else if (type == "transitive-verb") transitives.push_back(word);
        else if (type == "intransitive-verb") intransitives.push_back(word);
        else if (type == "conjunction") conjunctions.push_back(word);
        else {
            cout << "|" << word << "!" << endl;
        }
    }
    PartialSentence initial {
        " ", static_cast<int>(nouns.size()),
        static_cast<int>(transitives.size()),
        static_cast<int>(intransitives.size()),
        static_cast<int>(conjunctions.size()),
        commas, periods,
        false
    };
    vector<PartialSentence> options = {initial};
    int besti = 0;
    string bests = "";
    set<tuple<int, int, int, int, int, int, bool>> seen = {};
    while (options.size() != 0) {
        // cout << "----" << endl;
        vector<PartialSentence> newops = {};
        for (auto option: options) {
            cout << options.size() << endl;
            if (!option.ends_with_and) {
                int words = nouns.size() + transitives.size() + intransitives.size() + conjunctions.size() - option.noun - option.trans - option.intras - option.conjunction;
                if (words > besti) {
                    besti = words;
                    string s(1+all(option.sentence)-1);
                    bests = s;
                }
            }
            for (auto newop: option.repopulate(nouns, transitives, intransitives, conjunctions)) {
                auto u = newop.unique();
                if (!seen.count(u)) {
                    newops.push_back(newop);
                    seen.insert(u);
                }
            }
        }
        options = newops;
    }
    cout << besti << endl;
    cout << bests << endl;
}
int main() {
    // moo language - NOT WORKING
    setIO("", false);
    int num_test_cases = nxt();
    for (int test_case = 0; test_case < num_test_cases; test_case++) {
        solve_test_case();
    }
    return 0;
}
