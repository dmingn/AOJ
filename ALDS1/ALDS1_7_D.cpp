#include <cstdio>
#include <array>
#include <algorithm>

using namespace std;

const int32_t N = 40;
array<int32_t, N> preorder, inorder;
vector<int32_t> postorder;

void construct_postorder(int32_t s_pre, int32_t s_in, int32_t l) {
    if (l > 1) {
        int32_t r_pre = s_pre, r_in = s_in;
        while (inorder[r_in] != preorder[r_pre]) r_in++;

        construct_postorder(s_pre + 1, s_in, r_in - s_in);
        construct_postorder(s_pre + r_in + 1 - s_in, r_in + 1, s_in + l - r_in - 1);
    }

    if (l >= 1) {
        postorder.push_back(preorder[s_pre]);
    }

    return;
}

int main() {
    int32_t n;
    scanf("%d", &n);

    for (int32_t i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    for (int32_t i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    construct_postorder(0, 0, n);

    for (int32_t i = 0; i < n; i++) {
        if (i != 0) printf(" ");
        printf("%d", postorder[i]);
    }
    printf("\n");

    return 0;
}
