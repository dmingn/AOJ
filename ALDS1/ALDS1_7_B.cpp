#include <cstdio>
#include <array>
#include <algorithm>

using namespace std;

const int32_t N = 25;
array<int32_t, N> parent, left, right, sibling, degree, depth, height;

int32_t calc_depth_height(int32_t id, int32_t d) {
    depth[id] = d;

    int32_t height_l = 0, height_r = 0;
    if (left[id] != -1) height_l = calc_depth_height(left[id], d+1);
    if (right[id] != -1) height_r = calc_depth_height(right[id], d+1);

    height[id] = max(height_l, height_r);

    return height[id] + 1;
}

int main() {
    parent.fill(-1);
    left.fill(-1);
    right.fill(-1);
    sibling.fill(-1);
    degree.fill(0);
    int32_t n;

    scanf("%d", &n);
    for (int32_t i = 0; i < n; i++) {
        int32_t id, l, r;
        scanf("%d %d %d", &id, &l, &r);

        if (l != -1) {
            left[id] = l;
            degree[id]++;
            parent[l] = id;
            sibling[l] = r;
        }

        if (r != -1) {
            right[id] = r;
            degree[id]++;
            parent[r] = id;
            sibling[r] = l;
        }
    }

    int32_t id = 0;
    while (parent[id] != -1) id++;
    calc_depth_height(id, 0);

    for (int32_t id = 0; id < n; id++) {
        printf("node %d: parent = %d, sibling = %d, degree = %d, depth = %d, height = %d, ", id, parent[id], sibling[id], degree[id], depth[id], height[id]);

        if (parent[id] == -1) {
            printf("root");
        } else if (left[id] == -1 && right[id] == -1) {
            printf("leaf");
        } else {
            printf("internal node");
        }

        printf("\n");
    }

    return 0;
}
