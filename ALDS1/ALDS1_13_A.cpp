#include <iostream>
#include <array>
#include <numeric>

using namespace std;
using board_t = array<int8_t, 64>;

void put(board_t &board, int32_t r, int32_t c) {
    for (int32_t i = 0; i < 8; i++) {
        board[i*8+c] = -1;
        board[r*8+i] = -1;
        if (0 <= i+c-r && i+c-r < 8) board[i*8+i+c-r] = -1;
        if (0 <= r+c-i && r+c-i < 8) board[i*8+r+c-i] = -1;
    }

    board[r*8+c] = 1;

    return;
}

void show(const board_t &board) {
    for (int32_t r = 0; r < 8; r++) {
        for (int32_t c = 0; c < 8; c++) {
            cout << ((board[r*8+c] == 1) ? "Q" : ".");
        }
        cout << endl;
    }

    return;
}

bool dfs(const board_t &board, int32_t r) {
    if (r == 8) {
        show(board);
        return true;
    }

    for (int32_t c = 0; c < 8; c++) {
        if (board[r*8+c] == 1) {
            return dfs(board, r+1);
        } else if (board[r*8+c] == 0) {
            board_t board_new = board;
            put(board_new, r, c);
            if (dfs(board_new, r+1)) return true;
        }
    }

    return false;
}

int main() {
    int32_t k;
    cin >> k;

    board_t board;
    fill(board.begin(), board.end(), 0);

    for (int32_t i = 0; i < k; i++) {
        int32_t r, c;
        cin >> r >> c;
        put(board, r, c);
    }

    dfs(board, 0);

    return 0;
}
