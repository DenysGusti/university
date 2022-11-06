#include <iostream>
#include <cmath>

using namespace std;

void solve() {
    int64_t x{}, y{};
    cin >> x >> y;
    if ((abs(x) + abs(y)) % 2 == 0)
        cout << max(abs(x), abs(y)) << '\n';
    else
        cout << max(abs(x), abs(y - 1)) + 1 << '\n';
}

int main() {
    size_t t{};
    for(cin >> t; t > 0; --t)
        solve();
    return 0;
}