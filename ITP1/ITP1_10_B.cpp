#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int32_t n;

    cin >> n;

    vector<int32_t> s(n);

    for (int32_t i = 0; i < n; i++) {
        cin >> s[i];
    }

    double m = accumulate(s.begin(), s.end(), 0) / n;
    double v = accumulate(s.begin(), s.end(), 0, [](double sum, int32_t s_i) {
        return sum + (s_i - m) * (s_i - m);
    }) / n;

    cout << fixed << setprecision(5) << sqrt(v) << endl;

    return 0;
}
