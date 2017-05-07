#include <iostream>
#include <vector>

using namespace std;

void print(vector<int32_t> v) {
    for (uint32_t i = 0; i < v.size() - 1; i++) {
        cout << v[i] << " ";
    }
    cout << v[v.size() - 1] << endl;
}

int main() {
    int32_t N, steps = 0;

    cin >> N;

    vector<int32_t> A(N);

    for (int32_t i = 0; i < N; i++) {
        cin >> A[i];
    }

    for (int32_t i = 0; i < N; i++) {
        for (int32_t j = N - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                int32_t temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                steps++;
            }
        }
    }

    print(A);
    cout << steps << endl;

    return 0;
}
