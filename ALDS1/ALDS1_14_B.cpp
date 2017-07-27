#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string T, P;

    cin >> T >> P;

    uint64_t ht = 0, hp = 0, b = 1;
    for (uint32_t i = 0; i < P.length(); i++) {
        ht = (ht << 7) + T[i];
        hp = (hp << 7) + P[i];
        b = b << 7;
    }

    for (int32_t i = 0; i <= (int32_t)(T.length() - P.length()); i++) {
        if (ht == hp) if (T.substr(i, P.length()) == P) printf("%d\n", i);
        ht = (ht << 7) + T[i+P.length()] - b * T[i];
    }

    return 0;
}
