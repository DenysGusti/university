#include <iostream>

using namespace std;

bool is_prime(const int n) {
    if (n == 1 || n != 2 && !(n & 1))
        return false;
    for (int i = 3; i * i <= n; i += 2)
        if (!(n % i))
            return false;
    return true;
}

int main() {
    int a, b;

    for (bool finish = false; !finish;) {
        try {
            cout << "a, b = " << endl;
            a = 0;
            b = 0;
            cin >> a >> b;
            if (a > 0 && b > 0 && a < b)
                finish = true;
            else
                throw logic_error("enter positive numbers, a < b");
        } catch (const logic_error &e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    }

    bool primes = false;
    for (int i = a; i <= b; ++i)
        if (is_prime(i)) {
            primes = true;
            break;
        }

    cout << "Input:\na = " << a << ", b = " << b << "\nOutput:\nOn the interval [" << a << ", " << b << "] there " <<
         (primes ? "is at least one prime number" : "are no prime numbers") << endl;
    return 0;
}
