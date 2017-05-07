#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string w, t;
    int32_t count = 0;

    cin >> w;

    transform(w.cbegin(), w.cend(), w.begin(), ::tolower);

    while (cin >> t) {
        transform(t.cbegin(), t.cend(), t.begin(), ::tolower);
        if (w == t) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
