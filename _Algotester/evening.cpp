#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    long long y;
    cin >> a >> b >> c;
    auto d = (long double) a / b;
    for (y = (long long) ((c - 1) / (1 - d)); y - (long long) (d * y) != c; ++y) {}
    cout << a * y;
    return 0;
}
// 3 4 2 -> 15
