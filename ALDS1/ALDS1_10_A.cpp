#include <iostream>
#include <vector>

using namespace std;

int main() {
    int32_t n;
    cin >> n;

    vector<int32_t> fib(n+1);
    fib[0] = 1;
    fib[1] = 1;
    for (int32_t i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    cout << fib[n] << endl;

    return 0;
}
