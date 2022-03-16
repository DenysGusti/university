// Знайти суму всіх простих чисел, які є на відрізку [a, b] (a, b - вводяться користувачем).
#include <iostream>
#include <cmath>

using namespace std;
typedef unsigned long long ull;

bool is_prime(const ull &n) {
    if (n == 1 || (!(n & 1) && n != 2)) return false;
    for (ull i = 3; i <= sqrt(n); i += 2) if (!(n % i)) return false;
    return true;
}

int main() {
    ull s{}, a, b;
    cout << "primes in range [a, b]\na, b = ";
    cin >> a >> b;
    cout << "primes: ";
    for (ull i = a; i <= b; ++i) {
        if (is_prime(i)) {
            cout << i << ' ';
            s += i;
        }
    }
    cout << "\nsum = " << s << endl;
    return 0;
}