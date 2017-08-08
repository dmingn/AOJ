#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

template<typename T>
using point = tuple<uint32_t, T, T>;

template<typename T>
class KdTree {
private:
    struct node {
        point<T> p;
        node *l, *r;
        node(const point<T> &p) : p(p), l(nullptr), r(nullptr) {}
    };

    node *root;

    template<typename Iter>
    node *construct(Iter points_begin, Iter points_end, bool x) {
        uint32_t n = points_end - points_begin;
        if (n == 0) return nullptr;

        if (x) sort(points_begin, points_end, [](const point<T> &lhs, const point<T> &rhs){return get<1>(lhs) < get<1>(rhs);});
        else sort(points_begin, points_end, [](const point<T> &lhs, const point<T> &rhs){return get<2>(lhs) < get<2>(rhs);});

        node *nd = new node(points_begin[n/2]);
        nd->l = construct(points_begin, points_begin+n/2, !x);
        nd->r = construct(points_begin+n/2+1, points_end, !x);

        return nd;
    }

    void search(node *nd, T sx, T tx, T sy, T ty, bool x, vector<uint32_t> &vec) {
        if (nd == nullptr) return;

        if (sx <= get<1>(nd->p) && get<1>(nd->p) <= tx &&
            sy <= get<2>(nd->p) && get<2>(nd->p) <= ty) {
            vec.push_back(get<0>(nd->p));
        }

        if (x ? sx <= get<1>(nd->p) : sy <= get<2>(nd->p)) search(nd->l, sx, tx, sy, ty, !x, vec);
        if (x ? get<1>(nd->p) <= tx : get<2>(nd->p) <= ty) search(nd->r, sx, tx, sy, ty, !x, vec);

        return;
    }

public:
    KdTree(vector<point<T>> &points) : root(construct(points.begin(), points.end(), true)) {}

    void search(T sx, T tx, T sy, T ty, vector<uint32_t> &vec) {
        search(root, sx, tx, sy, ty, true, vec);
        return;
    }
};

int main() {
    int32_t n;
    scanf("%d", &n);

    vector<point<int32_t>> points(n);

    for (int32_t i = 0; i < n; i++) {
        int32_t x, y;
        scanf("%d %d", &x, &y);

        points[i] = make_tuple(i, x, y);
    }

    KdTree<int32_t> kdt(points);

    int32_t q;
    scanf("%d", &q);

    for (int32_t i = 0; i < q; i++) {
        int32_t sx, tx, sy, ty;
        scanf("%d %d %d %d", &sx, &tx, &sy, &ty);

        vector<uint32_t> res;
        kdt.search(sx, tx, sy, ty, res);

        sort(res.begin(), res.end());

        for (uint32_t id : res) printf("%u\n", id);
        printf("\n");
    }

    return 0;
}
