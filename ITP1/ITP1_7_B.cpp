#include <iostream>

using namespace std;

int main() {
    int32_t n, x;

    while (cin >> n >> x) {
        if (n == 0 && x == 0) {
            break;
        }

        int32_t count = 0;

        for (int32_t i = 1; i <= n - 2; i++) {
            for (int32_t j = i + 1; j <= n - 1; j++) {
                for (int32_t k = j + 1; k <= n; k++) {
                    if (i + j + k == x) {
                        count++;
                    }
                }
            }
        }

        cout << count << endl;
    }

    return 0;
}
