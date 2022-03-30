#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

std::vector<long long> a, b;

auto lower_than(const long long &s) {
    long long res{};
    long long index = b.size();
    for (const auto &el: a) {
        index = std::upper_bound(b.begin(), b.begin() + index, s - el) - b.begin();
        res += index;
    }
    return res;
}

int main() {
    long long m, n, k, tmp, l = LLONG_MIN, r = LLONG_MAX, res = -1;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        a.push_back(tmp);
    }
    std::cin >> m;
    for (int j = 0; j < m; ++j) {
        std::cin >> tmp;
        b.push_back(tmp);
    }
    std::cin >> k;
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    while (l <= r) {
        auto mid = (l + r) / 2;
        if (lower_than(mid) >= k) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << res << std::endl;
    return 0;
}
/*
3
2 3 4
3
3 2 1
4
-> 5

6
-20 -7 12 13 14 90
5
-8 -4 -2 0 30
5
-> -15
*/