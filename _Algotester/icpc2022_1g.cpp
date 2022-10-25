#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

uint64_t countBits(const uint64_t n) {
    if (n == 0)
        return 1;

    return static_cast<uint64_t>(log2(n)) + 1;
}

bool compare(const uint64_t x, const uint64_t y) {
    return countBits(x) < countBits(y);
}

bool is_div(const uint64_t x, const size_t i) {
    return !(x & (1 << i));
}

void solve() {
    size_t n{}, m{};
    cin >> n >> m;
    vector<uint64_t> row(n), col(m);
    for (auto &x: row)
        cin >> x;
    for (auto &x: col)
        cin >> x;

    uint64_t max_bit = countBits(
            max(*max_element(row.begin(), row.end(), compare), *max_element(col.begin(), col.end(), compare)));

//    cout << "max: " << max_bit << endl;

    uint64_t res{};

    for (size_t i = 0; i < max_bit; ++i) {
        size_t a = count_if(row.begin(), row.end(), [&](const auto x) { return !is_div(x, i); });
        size_t b = count_if(col.begin(), col.end(), [&](const auto x) { return !is_div(x, i); });
//        cout << a << ' ' << b << endl;
        if ((a + b) % 2 == 1) {
            cout << -1 << endl;
            return;
        }
        res += max(a, b) * (1 << i);
    }
    cout << res << endl;
}

int main() {
    size_t t{};
    for (cin >> t; t; --t)
        solve();
    return 0;
}

/*
1
4 5
32 64 96 128
160 96 32 224 128
*/
