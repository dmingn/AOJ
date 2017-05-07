#include <iostream>
#include <vector>

using namespace std;

int main() {
    int32_t r, c;

    cin >> r >> c;

    vector<vector<int32_t>> table(r + 1, vector<int32_t>(c + 1, 0));

    for (int32_t i = 0; i < r; i++) {
        for (int32_t j = 0; j < c; j++) {
            cin >> table[i][j];
            table[i][c] += table[i][j];
            table[r][j] += table[i][j];
            table[r][c] += table[i][j];
        }
    }

    for (int32_t i = 0; i < r + 1; i++) {
        for (int32_t j = 0; j < c + 1; j++) {
            cout << table[i][j];
            if (j != c) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    }

    return 0;
}
