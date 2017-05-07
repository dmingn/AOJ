#include <iostream>

using namespace std;

int main() {
    int64_t n, r_min, d_max = 1 - 1000000000;

    cin >> n >> r_min;

    for (int64_t i = 1; i < n; i++) {
        int64_t r;
        cin >> r;

        if (d_max < (r - r_min)) {
            d_max = r - r_min;
        }

        if (r < r_min) {
            r_min = r;
        }
    }

    cout << d_max << endl;

    return 0;
}
