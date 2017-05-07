#include <iostream>

using namespace std;

int main() {
    int x, i = 1;

    while (cin >> x)
        if (x == 0)
            break;
        else
            cout << "Case " << i++ << ": " <<  x << endl;

    return 0;
}
