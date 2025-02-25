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

int main() {
    // USACO 2020 December Contest, Bronze
    // Problem 1. Do You Know Your ABCs?
    // https://usaco.org/index.php?page=viewproblem2&cpid=1059
    setIO("", false);

    vector<long long> numbers = {0,0,0,0,0,0,0};
    cin >> numbers[0]
        >> numbers[1] >> numbers[2] >> numbers[3]
        >> numbers[4] >> numbers[5] >> numbers[6];

    long long target_sum = *std::max_element(numbers.begin(), numbers.end());
    numbers.erase(find(all(numbers), target_sum));
    long long smallest = *std::min_element(numbers.begin(), numbers.end());
    numbers.erase(find(all(numbers), smallest));
    long long second_smallest = *std::min_element(numbers.begin(), numbers.end());
    numbers.erase(find(all(numbers), second_smallest));
    for (long long remaining : numbers) {
        if (smallest + second_smallest + remaining == target_sum) {
            cout << smallest << " " << second_smallest << " " << remaining;
            return 0;
        }
    }
}
