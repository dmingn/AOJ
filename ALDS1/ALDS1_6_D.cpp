#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdint>

using namespace std;

int main() {
    int32_t n;

    cin >> n;
    vector<int32_t> w(n);
    for (int32_t i = 0; i < n; i++) {
        cin >> w[i];
    }

    vector<int32_t> sorted(w);
    sort(sorted.begin(), sorted.end());

    unordered_map<int32_t, int32_t> index;
    for (int32_t i = 0; i < n; i++) {
        index[sorted[i]] = i;
    }

    int32_t cost = 0;
    for (int32_t i = 0; i < n; i++) {
        if (w[i] != sorted[i]) {
            int32_t size = 1, sum = w[i], minval = INT32_MAX;
            int32_t j = index[w[i]], j_new;
            while (j != i) {
                size++;
                sum += w[j];
                minval = min(minval, w[j]);
                j_new = index[w[j]];
                w[j] = sorted[j];
                j = j_new;
            }

            cost += min(sum + minval * (size - 2), 2 * (sorted[0] + minval) + (sum - minval + sorted[0]) + sorted[0] * (size - 2));
        }
    }

    cout << cost << endl;

    return 0;
}
