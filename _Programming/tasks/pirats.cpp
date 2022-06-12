#include <iostream>
#include <cmath>

using namespace std;

int main() {
    for (int n = 1; n <= 14; n++) {
        uint64_t k = ((n & 1) ? 1 : (n - 1)) * static_cast<uint64_t>(pow(n, n)) - n + 1;
        cout << "n = " << n << "\ncoins: " << k << endl;
    }
    return 0;
}