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
    int32_t N;

    cin >> N;

    vector<int32_t> A(N);

    for (int32_t i = 0; i < N; i++) {
        cin >> A[i];
    }

    print(A);

    for (int32_t i = 1; i < N; i++) {
        int32_t key = A[i];
        int32_t j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;

        print(A);
    }

    return 0;
}
