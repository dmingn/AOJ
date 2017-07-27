#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    string T, P;

    cin >> T >> P;

    vector<uint32_t> sa;
    for (uint32_t i = 0; i < T.length(); i++) {
        sa.push_back(i);
    }

    sort(sa.begin(), sa.end(), [T](uint32_t a, uint32_t b) {return T.substr(a, T.length()-a) < T.substr(b, T.length()-b);});

    auto itr_lb = lower_bound(sa.begin(), sa.end(), P, [T](uint32_t i, string s) {return T.substr(i, T.length()-i) < s;});
    auto itr_ub = upper_bound(itr_lb, sa.end(), P, [T](string s, uint32_t i) {return s < T.substr(i, T.length()-i).substr(0, s.length());});

    vector<uint32_t> indexes;
    for (auto itr = itr_lb; itr != itr_ub; itr++) {
        indexes.push_back(*itr);
    }

    sort(indexes.begin(), indexes.end());

    for (uint32_t index : indexes) {
        cout << index << endl;
    }

    return 0;
}
