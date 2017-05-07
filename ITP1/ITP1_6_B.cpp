#include <iostream>
#include <vector>

using namespace std;

int main() {
    uint8_t suit;
    uint16_t n, num;
    vector<bool> cards(52, false);

    cin >> n;

    for (uint16_t i = 0; i < n; i++) {
        cin >> suit >> num;

        switch (suit) {
            case 'S':
                cards[0 * 13 + num - 1] = true;
                break;
            case 'H':
                cards[1 * 13 + num - 1] = true;
                break;
            case 'C':
                cards[2 * 13 + num - 1] = true;
                break;
            case 'D':
                cards[3 * 13 + num - 1] = true;
                break;
        }
    }

    for (uint16_t i = 0; i < 52; i++) {
        if (cards[i] == false) {
            switch (i / 13) {
                case 0:
                    cout << "S";
                    break;
                case 1:
                    cout << "H";
                    break;
                case 2:
                    cout << "C";
                    break;
                case 3:
                    cout << "D";
                    break;
            }

            cout << " " << i % 13 + 1 << endl;
        }

    }

    return 0;
}
