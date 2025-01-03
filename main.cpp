#include <bits/stdc++.h>
#define ITER(v) v.begin(), v.end()
using namespace std;

int main() {
    int l;
    cin >> l;
    vector<int> numbers(l * 2);

    for (int i = 0; i < l * 2; i++) {
        cin >> numbers[i];
    }

    sort(ITER(numbers));
    int best = -1;
    for (int a = 0; a < 2*l; a++) {
        for (int b = a+1; b < 2*l; b++) {
            // a and b are the two single kayaks
            auto tmpnums = numbers;
            tmpnums.erase(tmpnums.begin()+a);
            tmpnums.erase(tmpnums.begin()+b-1);  // Adjust index after first erase
            int t = 0;
            for (int d = 0; d < l-1; d++) {
                t += abs(tmpnums[d*2]-tmpnums[d*2+1]);
            }
            if (best == -1 || t < best) {
                best = t;
            }
        }
    }
    cout << best << endl;
    return 0;
}
