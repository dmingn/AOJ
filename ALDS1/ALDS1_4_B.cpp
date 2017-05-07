#include <iostream>
#include <vector>

using namespace std;

template<typename T>
bool binary_search(vector<T> S, T t) {
    uint32_t b = 0, e = S.size() - 1;
    while (b <= e) {
        uint32_t h = (b + e) / 2;
        if (S[h] == t) {
            return true;
        } else if (S[h] > t) {
            e = h - 1;
        } else {
            b = h + 1;
        }
    }

    return false;
}

int main() {
    uint32_t n, q, count = 0;

    cin >> n;
    vector<uint32_t> S(n);
    for (uint32_t &s : S) cin >> s;

    cin >> q;
    while (q--) {
        uint32_t t;
        cin >> t;
        if (binary_search(S, t)) count++;
    }

    cout << count << endl;

    return 0;
}
