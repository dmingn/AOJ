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
        int32_t mini = i;
        for (int32_t j = i; j < N; j++) {
            if (A[j] < A[mini]) {
                mini = j;
            }
        }

        if (i != mini) {
            int32_t temp = A[i];
            A[i] = A[mini];
            A[mini] = temp;
            steps++;
        }
    }

    print(A);
    cout << steps << endl;

    return 0;
}
