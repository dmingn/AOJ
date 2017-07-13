#include <iostream>
#include <vector>
#include <numeric>
#include <queue>

using namespace std;

int main() {
    int32_t n;
    cin >> n;

    vector<vector<int32_t>> A(n+1);

    for (int32_t i = 0; i < n; i++) {
        int32_t u, k;
        cin >> u >> k;

        for (int32_t j = 0; j < k; j++) {
            int32_t v;
            cin >> v;

            A[u].push_back(v);
        }
    }

    vector<bool> visited(n+1);
    fill(visited.begin(), visited.end(), false);
    vector<int32_t> d(n+1);
    fill(d.begin(), d.end(), -1);
    queue<int32_t> tovisit;
    visited[1] = true;
    d[1] = 0;
    tovisit.push(1);

    while (!tovisit.empty()) {
        int32_t u = tovisit.front();
        tovisit.pop();

        for (int32_t v : A[u]) {
            if (!visited[v]) {
                visited[v] = true;
                d[v] = d[u] + 1;
                tovisit.push(v);
            }
        }
    }

    for (int32_t i = 1; i <= n; i++) {
        cout << i << " " << d[i] << endl;
    }

    return 0;
}
