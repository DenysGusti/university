#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    int n;
    bool flag = true;
    std::cin >> n;
    std::vector<int> a(n);
    std::set<int> sums;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (i && a[i - 1] >= a[i]) {
            flag = false;
            break;
        }
    }
    if (flag)
        for (const auto &el: a) {
            if (sums.find(el) != sums.end()) {
                flag = false;
                break;
            }
            for (const auto &s: std::set<int>(sums)) {
                auto tmp = s + el;
                if (tmp <= a.back())
                    sums.insert(tmp);
            }
            sums.insert(el);
        }
    std::cout << (flag ? "Yes" : "No") << std::endl;
    return 0;
}