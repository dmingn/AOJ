#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int32_t n;

    while (cin >> n, n != 0) {
        vector<double> s(n);

        for (int32_t i = 0; i < n; i++) {
            cin >> s[i];
        }

        double m = accumulate(s.begin(), s.end(), 0.0) / n;
        double v = accumulate(s.begin(), s.end(), 0.0, [m](double sum, double s_i) {
            return sum + (s_i - m) * (s_i - m);
        }) / n;

        cout << fixed << setprecision(5) << sqrt(v) << endl;
    }

    return 0;
}
