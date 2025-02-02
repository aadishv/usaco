#include <bits/stdc++.h>
#define vi vector<int>
#define all(it) it.begin(), it.end()
#define ll long long
#define cast static_cast
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
enum Word { FALSE = 0, TRUE = 1, AND = 2, OR = 3 };
bool eval(vector<Word> ws) {

    auto words = ws;
    // evaluate all ands
    while (words.size() > 1) {
        auto first_and = find(all(words), Word::AND);
        if (first_and == words.end()) break;
        int p = first_and-words.begin();
        words[p-1] = cast<Word>(words[p-1] && words[p+1]);
        words.erase(first_and, first_and+2);
    }
    // evaluate all ors
    while (words.size() > 1) {
        auto first_and = find(all(words), Word::OR);
        if (first_and == words.end()) break;
        int p = first_and-words.begin();
        words[p-1] = cast<Word>(words[p-1] || words[p+1]);
        words.erase(first_and, first_and+2);
    }
    return cast<bool>(words[0]);
}
int main() {
    // ios_base::sync_with_stdio(false); cin.tie(0);
    // logical moos - NOT WORKING
    int nwords = nxt(), nqueries = nxt();
    // dbg<int>({nwords, nqueries});
    vector<Word> words(nwords);
    for (auto& word: words) {
        string s; cin >> s;
        if (s == "false") word = Word::FALSE;
        else if (s == "true") word = Word::TRUE;
        else if (s == "and") word = Word::AND;
        else word = Word::OR;
    }
    for (int q = 0; q < nqueries; q++) {
        int start = nxt()-1, end = nxt()-1;
        string t; cin >> t;
        bool target = t == "true";
        if (eval(words) == target) {
            cout << "Y";
        } else {
            vector<Word> current(words.begin()+start, words.begin()+end+1);
            auto news = words;
            news.erase(news.begin()+start, news.begin()+end);
            news[start] = cast<Word>(1-eval(current));
            if (eval(news)) cout << "Y";
            else cout << N;
        }
    }
    return 0;
}
