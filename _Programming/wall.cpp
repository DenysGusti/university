#include <iostream>

using namespace std;

int main() {
    unsigned long long d, a = 0, b = 1, c;
    cin >> d;
    for (unsigned long long i = 0; i < d; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    cout << c << endl;
    return 0;
}