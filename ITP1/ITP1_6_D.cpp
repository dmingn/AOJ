#include <iostream>
#include <vector>

using namespace std;

int main() {
    int32_t n, m;

    cin >> n >> m;

    vector<vector<int32_t>> A(n, vector<int32_t>(m));
    vector<int32_t> b(m);

    for (int32_t i = 0; i < n; i++) {
        for (int32_t j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }

    for (int32_t i = 0; i < m; i++) {
        cin >> b[i];
    }

    for (int32_t i = 0; i < n; i++) {
        int32_t c_i = 0;

        for (int32_t j = 0; j < m; j++) {
            c_i += A[i][j] * b[j];
        }

        cout << c_i << endl;
    }

    return 0;
}
