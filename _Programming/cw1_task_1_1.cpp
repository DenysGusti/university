// Для введених цілих чисел a, b, знайдіть суму усіх чисел з [a, b], які мають рівно три дільники.
#include <iostream>
#include <cmath>

using namespace std;
typedef unsigned long long ull;

bool is_prime(const ull &n) {
    if (n == 1 || (!(n & 1) && n != 2))
        return false;
    for (ull i = 3; i * i <= n; i += 2)
        if (!(n % i))
            return false;
    return true;
}

int main() {
    ull s{}, a, b; // рівно 3 дільники мають квадрати простих чисел (4: 1, 2, 4; 9: 1, 3, 9; 25: 1, 5, 25)
    cout << "[a, b]\na, b = ";
    cin >> a >> b;
    cout << "numbers: ";
    for (ull i = (ull) sqrt(a); i * i <= b; ++i) {
        if (is_prime(i)) {
            cout << i * i << ' ';
            s += i * i;
        }
    }
    cout << "\nsum = " << s << endl;
    return 0;
}