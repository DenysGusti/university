#include <iostream>
#include <cmath>

using namespace std;

double volume(const int &r, const int &d, const int &c, const double &h) {
    double inner = (r - d <= h) ? 0 : (r - d <= -h) ? 4 * pow(r - d, 3) : pow(r - d - h, 2) * (2 * (r - d) + h);
    return M_PI * (c * pow(r - h, 2) * (2 * r + h) - (c - 1) * inner) / 3;
}

int main() {
    int r, d, c, k;
    cin >> r >> d >> c >> k;
    double h, left = -r, right = r, v;
    for (; right - left > 1e-5; ((v > k) ? left : right) = h) {
        h = (left + right) / 2;
        v = volume(r, d, c, h);
    }
    cout << h << endl;
    return 0;
}
/*
3 1 2 2
2.668087408
2 1 1 17
-0.01948425174
*/