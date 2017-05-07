#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    string str;
    cin >> str;

    stack<uint32_t> s;
    vector<pair<uint32_t, uint32_t>> v;
    for (uint32_t i = 0; i < str.length(); i++) {
        if (str[i] == '\\') {
            s.push(i);
        } else if (str[i] == '/' && !s.empty()) {
            uint32_t j = s.top();
            s.pop();
            uint32_t area = i - j;
            while (!v.empty() && v.back().first > j) {
                area += v.back().second;
                v.pop_back();
            }
            v.push_back(make_pair(j, area));
        }
    }

    cout << accumulate(v.begin(), v.end(), 0, [](uint32_t sum, pair<uint32_t, uint32_t> p) {
        return sum + p.second;
    }) << endl;
    cout << v.size();
    for (pair<uint32_t, uint32_t> p : v) cout << " " << p.second;
    cout << endl;

    return 0;
}
