#include <iostream>

#define p 1234567891
using namespace std;
long long int a, b, s = 0;

long long int bin_pow_mod(long long int x, long long int y) {
    long long int res = 1;
    while (y) {
        if (y & 1) res = (res * x) % p;
        x = (x * x) % p;
        y >>= 1;
    }
    return res;
}

void lucky_number_constructor(long long int n) {
    if (n > b) return;
    if (n >= a) s = (s + bin_pow_mod(n % p, n % (p - 1))) % p;
    lucky_number_constructor(10 * n + 4);
    lucky_number_constructor(10 * n + 7);
}

int main() {
    cin >> a >> b;
    lucky_number_constructor(0);
    cout << s;
    return 0;
}