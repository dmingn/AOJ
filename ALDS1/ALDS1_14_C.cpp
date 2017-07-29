#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

template<typename T>
class PMA {
private:
    uint32_t id = 0;

public:
    struct Node {
        uint32_t id;
        bool accepted = false;
        unordered_map<T, Node*> children;
        Node *failure = nullptr;
    };

    Node *root;

    int32_t insert(const vector<T> &vec) {
        Node *node = root;
        for (T v : vec) {
            auto itr = node->children.find(v);
            if (itr != node->children.end()) {
                node = itr->second;
            } else {
                node->children[v] = new Node;
                node->children[v]->id = id++;
                node = node->children[v];
            }
        }

        node->accepted = true;

        return node->id;
    }

    Node *transition(Node *node, T v) {
        while (node != nullptr) {
            auto itr = node->children.find(v);
            if (itr != node->children.end()) {
                return itr->second;
            } else {
                node = node->failure;
            }
        }
        return root;
    }

    void link_failure() {
        queue<Node*> tovisit;
        tovisit.push(root);
        while (!tovisit.empty()) {
            Node *node = tovisit.front();
            tovisit.pop();

            for (auto p : node->children) {
                T v = p.first;
                Node *child = p.second;

                child->failure = transition(node->failure, v);

                tovisit.push(child);
            }
        }
        return;
    }

    PMA() {
        root = new Node;
        root->id = id++;
    }
};

int main() {
    int32_t H, W, R, C;
    cin >> H >> W;

    vector<vector<uint8_t>> T(H);
    for (int32_t i = 0; i < H; i++) {
        string temp;
        cin >> temp;
        T[i] = vector<uint8_t>(temp.begin(), temp.end());
    }

    cin >> R >> C;

    vector<vector<uint8_t>> P(R);
    for (int32_t i = 0; i < R; i++) {
        string temp;
        cin >> temp;
        P[i] = vector<uint8_t>(temp.begin(), temp.end());
    }

    PMA<uint8_t> pma_p;
    vector<uint32_t> M;
    for (vector<uint8_t> vec : P) M.push_back(pma_p.insert(vec));
    pma_p.link_failure();

    PMA<uint32_t> pma_m;
    pma_m.insert(M);
    pma_m.link_failure();

    vector<vector<uint32_t>> T2(W);

    for (vector<uint8_t> vec : T) {
        PMA<uint8_t>::Node *node = pma_p.root;
        for (uint32_t i = 0; i < vec.size(); i++) {
            node = pma_p.transition(node, vec[i]);
            T2[i].push_back(node->id);
        }
    }

    vector<pair<uint32_t, uint32_t>> res;
    for (int32_t c = 0; c < W; c++) {
        PMA<uint32_t>::Node *node = pma_m.root;
        for (int32_t r = 0; r < H; r++) {
            node = pma_m.transition(node, T2[c][r]);
            if (node->accepted) {
                res.push_back(make_pair(r - R + 1, c - C + 1));
            }
        }
    }

    sort(res.begin(), res.end());

    for (auto p : res) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
