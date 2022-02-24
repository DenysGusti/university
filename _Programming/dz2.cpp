#include <iostream>

using namespace std;

int main() {
    double k1, k2, l1, l2;
    cout << "y=kx+l\nk1 l1: ";
    cin >> k1 >> l1;
    cout << "k2 l2: ";
    cin >> k2 >> l2;
    if (k1 == k2) {
        cout << "прямі паралельні";
    } else {
        double x = (l2 - l1) / (k1 - k2), y = k1 * x + l1;
        cout << "прямі перетинаються в точці (" << x << ", " << y << ")";
    }
    return 0;
}