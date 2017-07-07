#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Vector2d {
public:
    double x;
    double y;

    Vector2d(double x, double y) : x(x), y(y) {}
    Vector2d(const Vector2d &p) : x(p.x), y(p.y) {}

    Vector2d rotate60() {
        return Vector2d((x - sqrt(3) * y) / 2, (sqrt(3) * x + y) / 2);
    }
};

Vector2d operator+(const Vector2d& p1, const Vector2d& p2) {return Vector2d(p1.x + p2.x, p1.y + p2.y);}
Vector2d operator-(const Vector2d& p1, const Vector2d& p2) {return Vector2d(p1.x - p2.x, p1.y - p2.y);}
Vector2d operator*(const Vector2d& p1, int32_t n) {return Vector2d(p1.x * n, p1.y * n);}
Vector2d operator*(const Vector2d& p1, double d) {return Vector2d(p1.x * d, p1.y * d);}
Vector2d operator/(const Vector2d& p1, int32_t n) {return Vector2d(p1.x / n, p1.y / n);}
ostream& operator<<(ostream& os, const Vector2d& p) {
    os << fixed << setprecision(8) << p.x << " " << p.y;
    return os;
};


void koch_curve(int32_t n, Vector2d p1, Vector2d p2) {
    if (n > 0) {
        Vector2d s = p1 + (p2 - p1) / 3;
        Vector2d t = p1 + (p2 - p1) * 2 / 3;
        Vector2d u = s + (t - s).rotate60();

        koch_curve(n-1, p1, s);
        cout << s << endl;
        koch_curve(n-1, s, u);
        cout << u << endl;
        koch_curve(n-1, u, t);
        cout << t << endl;
        koch_curve(n-1, t, p2);
    }

    return;
}

int main() {
    int32_t n;

    cin >> n;

    cout << Vector2d(0, 0) << endl;
    koch_curve(n, Vector2d(0, 0), Vector2d(100, 0));
    cout << Vector2d(100, 0) << endl;

    return 0;
}
