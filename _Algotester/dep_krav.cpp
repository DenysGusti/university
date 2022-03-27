#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef unsigned long long ull;
typedef long double ld;

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<ull> a(n);
    for (auto &el: a)
        std::cin >> el;
    ld l = 0, r = *std::max_element(a.begin(), a.end());
    ld mid = 0;
    while (r - l > 1e-5) {
        mid = (l + r) / 2;
        (std::accumulate(a.begin(), a.end(), 0, [mid](auto x, auto y) { return x + (int) y / mid; }) < m ? r : l) = mid;
    }
    std::cout << mid << std::endl;
    return 0;
}
/*
3 4
1 10 5
*/