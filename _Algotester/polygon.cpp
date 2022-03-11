#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    short n, i;
    cin >> n;
    long double eps = 1e-11, R, sum_phi, l = n / 2.0, r = n * n;
    for (; r - l > eps; ((sum_phi > 2 * M_PI) ? l : r) = R)
        for (R = ((n < l + r) ? l + r : n) / 2, sum_phi = 0, i = 1; i <= n; ++i)
            sum_phi += acos(1 - i * i / (2 * R * R));
    cout << fixed << setprecision(4) << R << endl;
    return 0;
}
