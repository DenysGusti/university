#include <iostream>
#include <cmath>

using namespace std;

int main() {
    unsigned long long int n, s = 0, i = 0, b = 1;
    cin >> n;
    cout << n << " = ";
    while (n) {
        s += n % 10 * b;
        b *= 2;
        n /= 10;
    }
    cout << s;
    return 0;
}