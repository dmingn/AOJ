#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int a, b;

    cin >> a >> b;

    cout << a / b << " " << a % b << " " <<  fixed << setprecision(5) << (double) a / b << endl;

    return 0;
}
