#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    string T, P;

    cin >> T >> P;

    vector<pair<string, uint32_t>> sa;
    for (uint32_t i = 0; i < T.length(); i++) {
        sa.push_back(make_pair(T.substr(i, T.length()-i), i));
    }

    sort(sa.begin(), sa.end());

    auto itr_lb = lower_bound(sa.begin(), sa.end(), P, [](pair<string, uint32_t> p, string s) {return p.first < s;});
    auto itr_ub = upper_bound(sa.begin(), sa.end(), P, [](string s, pair<string, uint32_t> p) {return s < p.first.substr(0, s.length());});

    vector<uint32_t> indexes;
    for (auto itr = itr_lb; itr != itr_ub; itr++) {
        indexes.push_back((*itr).second);
    }

    sort(indexes.begin(), indexes.end());

    for (uint32_t index : indexes) {
        cout << index << endl;
    }

    return 0;
}
