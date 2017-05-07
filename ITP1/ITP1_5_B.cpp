#include <iostream>

using namespace std;

int main() {
    uint16_t H, W;

    while (cin >> H >> W) {
        if (H == 0 && W == 0)
            break;

        for (uint16_t i = 0; i < H; i++) {
            for (uint16_t j = 0; j < W; j++)
                if (i == 0 || i == H-1 || j == 0 || j == W-1)
                    cout << "#";
                else
                    cout << ".";

            cout << endl;
        }

        cout << endl;
    }

    return 0;
}
