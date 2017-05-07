#include <iostream>
#include <array>

using namespace std;

enum dir_t {NORTH, EAST, WEST, SOUTH, CLKW, CCLKW};
enum face_t {TOP, BOTTOM, FRONT, BACK, LEFT, RIGHT};

class Dice {
public:
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
    int32_t top, bottom, front, back, left, right;

    cin >> top >> front >> right >> left >> back >> bottom;
    Dice d1(top, bottom, front, back, left, right);

    cin >> top >> front >> right >> left >> back >> bottom;
    Dice d2(top, bottom, front, back, left, right);

    if (d1.identical_with(d2)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
