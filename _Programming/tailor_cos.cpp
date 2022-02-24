#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

unsigned long long fact(int n) {
    unsigned long long f = 1;
    for (int i = 1; i <= n; ++i)  f *= i;
    return f;
}

long double tailor_cos(long double x, long double err) {
    long double s = 0, p = 1;
    for (int i = 0; fact(2 * i) <= 1 / err; ++i) {
        s += p / fact(2 * i);
        p *= -x * x;
    }
    return s;
}


int main() {
    long double a, eps;
    cout << "cos(x)\nenter x and epsilon: ";
    cin >> a >> eps;
    a = fmod(a, M_PI);
    long double b = tailor_cos(a, eps);
    cout << fixed << setprecision((int) log10(1 / eps)) << b << endl;
    return 0;
}