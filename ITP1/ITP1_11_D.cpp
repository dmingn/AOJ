#include <iostream>
#include <array>
#include <vector>

using namespace std;

enum dir_t {NORTH, EAST, WEST, SOUTH, CLKW, CCLKW};
enum face_t {TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT};

class Dice {
public:
    Dice() {
        val[TOP]    = 0;
        val[BOTTOM] = 0;
        val[FRONT]  = 0;
        val[BACK]   = 0;
        val[LEFT]   = 0;
        val[RIGHT]  = 0;
    }

    Dice(int32_t top, int32_t bottom, int32_t front, int32_t back, int32_t left, int32_t right) {
        val[TOP]    = top;
        val[BOTTOM] = bottom;
        val[FRONT]  = front;
        val[BACK]   = back;
        val[LEFT]   = left;
        val[RIGHT]  = right;
    }

    int32_t operator[](face_t f) {
        return val[f];
    }

    bool operator== (const Dice &d2) {
        return (*this).val == d2.val;
    }

    void roll(dir_t dir) {
        switch (dir) {
            case NORTH: inner_roll(TOP, FRONT, BOTTOM, BACK); break;
            case EAST:  inner_roll(TOP, LEFT, BOTTOM, RIGHT); break;
            case WEST:  inner_roll(TOP, RIGHT, BOTTOM, LEFT); break;
            case SOUTH: inner_roll(TOP, BACK, BOTTOM, FRONT); break;
            case CLKW:  inner_roll(FRONT, RIGHT, BACK, LEFT); break;
            case CCLKW: inner_roll(FRONT, LEFT, BACK, RIGHT); break;
        }
    }

    bool identical_with(Dice d) {
        for (int32_t i = 0; i < 6; i++) {
            for (int32_t j = 0; j < 4; j++) {
                if (d == *this) {
                    return true;
                }
                d.roll(CLKW);
            }

            if (i % 2 == 0) {
                d.roll(NORTH);
            } else {
                d.roll(WEST);
            }
        }

        return false;
    }

private:
    array<int32_t, 6> val;

    void inner_roll(face_t f1, face_t f2, face_t f3, face_t f4) {
        int32_t temp;
        temp = val[f1];
        val[f1] = val[f2];
        val[f2] = val[f3];
        val[f3] = val[f4];
        val[f4] = temp;

        return;
    }
};

int main() {
    int32_t n, top, bottom, front, back, left, right;

    cin >> n;

    vector<Dice> dices(n);

    for (int32_t i = 0; i < n; i++) {
        cin >> top >> front >> right >> left >> back >> bottom;
        Dice d(top, bottom, front, back, left, right);

        for (int32_t j = 0; j < i; j++) {
            if (d.identical_with(dices[j])) {
                cout << "No" << endl;
                return 0;
            }
        }

        dices[i] = d;
    }

    cout << "Yes" << endl;

    return 0;
}
