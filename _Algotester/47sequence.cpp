#include <iostream>
#include <array>

using namespace std;

int main() {
    array<unsigned long long, 83> fib{};
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < 83; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    unsigned long long n, k;
    cin >> n >> k;
    if (k > fib[n + 2])
        cout << "Flowers";
    else {
        for (auto order{k}, i = n + 2; i >= 3; --i) {
            if (order > fib[i - 2]) { // F(i-3)... | F(i-2)...
                cout << 7;
                order -= fib[i - 2]; // вліво
            } else {
                cout << 4;
                order += fib[i - 3]; // вправо
            }
        }
    }
    cout << endl;
    return 0;
}