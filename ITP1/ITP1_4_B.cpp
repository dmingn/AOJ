#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    double r;

    cin >> r;

    cout << fixed << setprecision(5) << atan(1) * 4.0 * r * r << " " << 8.0 * atan(1) * r << endl;

    return 0;
}
