#include <iostream>
#include <array>
#include <vector>

using namespace std;

class Board {
    friend bool operator==(const Board &b1, const Board &b2);
    friend bool operator!=(const Board &b1, const Board &b2);

private:
    uint64_t board;

public:
    Board() {
        board = 0;
    }

    void set(int32_t r, int32_t c, int64_t v) {
        uint32_t shift = 4 * (r * 3 + c);
        uint64_t mask = 0xf;
        board = (board & ~(mask << shift)) | (v << shift);
        return;
    }

    int32_t get(int32_t r, int32_t c) const {
        int32_t shift = 4 * (r * 3 + c);
        return (board >> shift) & 0xf;
    }

    void swap(int32_t r1, int32_t c1, int32_t r2, int32_t c2) {
        int32_t temp = get(r1, c1);
        set(r1, c1, get(r2, c2));
        set(r2, c2, temp);
        return;
    }

    void show() const {
        cout << hex << board << endl;
    }
};

bool operator==(const Board &b1, const Board &b2) {return b1.board == b2.board;};
bool operator!=(const Board &b1, const Board &b2) {return !(b1 == b2);}

int32_t manhattan(const Board &board) {
    int32_t d = 0;

    for (int32_t r = 0; r < 3; r++) {
        for (int32_t c = 0; c < 3; c++) {
            int32_t v = board.get(r, c);
            if (v != 0) d += abs(r - (v-1) / 3) + abs(c - (v-1) % 3);
        }
    }

    return d;
}

vector<Board> children(const Board &board) {
    vector<Board> c;
    int32_t zr, zc;

    for (int32_t z = 0; z < 9; z++) {
        if (board.get(z/3, z%3) == 0) {
            zr = z/3;
            zc = z%3;
            break;
        }
    }

    array<int32_t, 4> dr = {1, 0, -1, 0}, dc = {0, 1, 0, -1};

    for (int32_t i = 0; i < 4; i++) {
        if (0 <= zr+dr[i] && zr+dr[i] < 3 && 0 <= zc+dc[i] && zc+dc[i] < 3) {
            Board board_new = board;
            board_new.swap(zr, zc, zr+dr[i], zc+dc[i]);
            c.push_back(board_new);
        }
    }

    return c;
}

bool dfs(const Board &board, const Board &parent, int32_t depth, int32_t dist, int32_t limit) {
    if (dist == 0) {
        cout << depth << endl;
        return true;
    }

    if (depth + dist > limit) return false;

    bool flag = false;
    for (Board child : children(board)) {
        if (child != parent) {
            if (dfs(child, board, depth + 1, manhattan(child), limit)) {
                flag = true;
                break;
            }
        }
    }

    return flag;
}


int main() {
    Board board;

    for (int32_t r = 0; r < 3; r++) {
        for (int32_t c = 0; c < 3; c++) {
            int32_t v;
            cin >> v;
            board.set(r, c, v);
        }
    }

    int32_t limit = 0;

    while (!dfs(board, board, 0, manhattan(board), limit)) limit++;

    return 0;
}
