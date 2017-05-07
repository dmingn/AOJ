#include <iostream>
#include <vector>

using namespace std;

uint32_t encode(string str) {
    uint32_t val = 0;
    for (uint8_t c : str) {
        switch (c) {
            case 'A': val = val * 4 + 1; break;
            case 'C': val = val * 4 + 2; break;
            case 'G': val = val * 4 + 3; break;
            case 'T': val = val * 4 + 4; break;
        }
    }
    return val - 1;
}

int main() {
    uint32_t n;
    vector<bool> dict(22369619, false);

    cin >> n;
    while (n--) {
        string op, str;
        cin >> op >> str;

        if (op == "insert") {
            dict[encode(str)] = true;
        } else if (op == "find") {
            cout << (dict[encode(str)] ? "yes" : "no") << endl;
        }
    }

    return 0;
}
