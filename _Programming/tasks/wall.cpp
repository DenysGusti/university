#include <iostream>

using namespace std;

int main() {
    uint64_t d, a = 0, b = 1, c;
    cout << "d = ";
    cin >> d;
    for (uint64_t i = 0; i < d; ++i) {
        c = a + b;
        a = b;
        b = c;
    }
    cout << c << endl;
    return 0;
}