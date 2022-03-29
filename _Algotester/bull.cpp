#include <iostream>
#include <numeric>

int main() {
    unsigned long long n, m, a, b;
    std::cin >> n >> m >> a >> b;
    auto d = std::gcd(a, b);
    a /= d, b /= d;
    auto c = std::min(n / a, m / b);
    std::cout << a * c << ' ' << b * c << std::endl;
    return 0;
}
// 4 6 6 8