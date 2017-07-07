#include <cstdio>
#include <array>
#include <algorithm>

using namespace std;

const int32_t N = 100000;
array<int32_t, N> parent, depth;
array<vector<int32_t>, N> children;

void calc_depth(int32_t id, int32_t d) {
    depth[id] = d;
    for (int32_t id_c : children[id]) calc_depth(id_c, d+1);
    return;
}

int main() {
    parent.fill(-1);
    int32_t n;

    scanf("%d", &n);
    for (int32_t i = 0; i < n; i++) {
        int32_t id;
        scanf("%d", &id);

        int32_t k;
        scanf("%d", &k);
        for (int32_t j = 0; j < k; j++) {
            int32_t c;
            scanf("%d", &c);
            parent[c] = id;
            children[id].push_back(c);
        }
    }

    int32_t id = 0;
    while (parent[id] != -1) id++;
    calc_depth(id, 0);

    for (int32_t id = 0; id < n; id++) {
        printf("node %d: parent = %d, depth = %d, ", id, parent[id], depth[id]);

        if (parent[id] == -1) {
            printf("root");
        } else if (children[id].empty()) {
            printf("leaf");
        } else {
            printf("internal node");
        }

        printf(", [");
        for (int32_t id_c : children[id]) {
            if (id_c != children[id][0]) printf(", ");
            printf("%d", id_c);
        }
        printf("]\n");
    }

    return 0;
}
