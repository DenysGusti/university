#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double x, k, r;
    cin >> x >> k >> r;
    cout << setprecision(9) << 2 * M_PI * r * k * x << endl;
    return 0;
}

