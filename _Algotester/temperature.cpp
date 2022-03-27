#include <iostream>
#include <cmath>
#include <algorithm>

typedef long long ll;
typedef long double ld;

int main() {
    ll n, k, a, b, max_t, min_t;
    std::cin >> n >> k >> a >> b;
    auto x = (ld) (b - a) / (2 * k), y = (ld) (n - 1) / 2;
    max_t = std::max(k * (ll) std::floor(y + x) + a, -k * (ll) std::ceil(y + x) + b + k * (n - 1));
    min_t = std::min(-k * (ll) std::floor(y - x) + a, k * (ll) std::ceil(y - x) + b - k * (n - 1));
    std::cout << max_t << ' ' << min_t << std::endl;
    return 0;
}
/*
4 7
-10 1
*/