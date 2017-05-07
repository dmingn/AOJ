#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void print(vector<T> v, uint8_t delimiter = ' ') {
    for (uint32_t i = 0; i < v.size() - 1; i++) {
        cout << v[i] << delimiter;
    }
    cout << v[v.size() - 1] << endl;
}

template<typename T>
int32_t insertion_sort(vector<T> &v, int64_t g) {
    int32_t count = 0;
    for (int64_t i = g; i < (int64_t) v.size(); i++) {
        int64_t val = v[i];
        int64_t j = i - g;
        while (j >= 0 && v[j] > val) {
            v[j + g] = v[j];
            j = j - g;
            count++;
        }
        v[j + g] = val;
    }

    return count;
}

template<typename T>
void shell_sort(vector<T> &v) {
    int32_t count = 0;

    vector<int64_t> G = {1};
    for (int32_t i = 0; 4 * G[i] <= (int64_t) v.size() ; i++) {
        G.push_back(4 * G[i]);
    }
    reverse(G.begin(), G.end());

    cout << G.size() << endl;
    print(G);

    for (int64_t i = 0; i < (int64_t) G.size(); i++) {
        count += insertion_sort(v, G[i]);
    }

    cout << count << endl;

    return;
}

int main() {
    int64_t N;

    cin >> N;

    vector<int64_t> A(N);

    for (int64_t i = 0; i < N; i++) cin >> A[i];

    shell_sort(A);
    print(A, '\n');

    return 0;
}
