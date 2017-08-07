#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

using namespace std;

template<typename T>
class RmQ {
private:
    uint32_t n;
    T max;
    vector<T> vec;

    T inner_find(uint32_t a, uint32_t b, uint32_t k, uint32_t l, uint32_t r) {
        if (r <= a || b <= l) {
            return max;
        }
        if (a <= l && r <= b) {
            return vec[k];
        } else {
            int val_l = inner_find(a, b, k * 2 + 1, l, (l + r) / 2);
            int val_r = inner_find(a, b, k * 2 + 2, (l + r) / 2 , r);
            return min(val_l, val_r);
        }
    }

public:
    RmQ(uint32_t num, T max) : max(max) {
        n = (uint32_t)pow(2, ceil(log2(num)));
        vec.resize(2 * n - 1);
        fill(vec.begin(), vec.end(), max);
    }

    void update(uint32_t i, T x) {
        i += n - 1;
        vec[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            vec[i] = min(vec[i * 2 + 1], vec[i * 2 + 2]);
        }
    }

    T find(uint32_t a, uint32_t b) {
        return inner_find(a, b, 0, 0, n);
    }
};

int main() {
    int32_t n, q;
    scanf("%d %d", &n, &q);

    RmQ<int32_t> rmq(n, INT32_MAX);

    for (int32_t i = 0; i < q; i++) {
        int32_t com, x, y;
        scanf("%d %d %d", &com, &x, &y);

        if (com) printf("%d\n", rmq.find(x, y+1));
        else rmq.update(x, y);
    }

    return 0;
}
