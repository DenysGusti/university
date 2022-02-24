#include <iostream>
#include <cmath>

using namespace std;

int main() {
    for (short n = 1; n <= 14; n++) {
        long long k = ((n & 1) ? 1 : (n - 1)) * (long long) pow(n, n) - n + 1;
        cout << "n = " << n << "\ncoins: " << k << endl;
    }
    return 0;
}