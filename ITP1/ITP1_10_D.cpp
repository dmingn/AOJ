#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int32_t n;

    cin >> n;

    vector<double> d(n);

    for (int32_t i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int32_t i = 0; i < n; i++) {
        double y;
        cin >> y;
        d[i] = abs(d[i] - y);
    }

    cout << fixed << setprecision(5) << accumulate(d.begin(), d.end(), 0.0) << endl;
    cout << fixed << setprecision(5) << sqrt(accumulate(d.begin(), d.end(), 0.0, [](double sum, double d_i) {
        return sum + d_i * d_i;
    })) << endl;
    cout << fixed << setprecision(5) << pow(accumulate(d.begin(), d.end(), 0.0, [](double sum, double d_i) {
        return sum + d_i * d_i * d_i;
    }), 1.0 / 3.0) << endl;
    cout << fixed << setprecision(5) << *max_element(d.begin(), d.end()) << endl;

    return 0;
}
