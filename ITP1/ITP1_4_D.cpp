#include <iostream>

using namespace std;

int main() {
    int64_t n, a;

    cin >> n >> a;

    int64_t min = a, max = a, sum = a;

    for (int64_t i = 1; i < n; i++) {
        cin >> a;
        if (a < min)
            min = a;
        if (max < a)
            max = a;
        sum += a;
    }

    cout << min << " " << max << " " << sum << endl;
}
