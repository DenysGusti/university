#include <iostream>
#include <numeric>

using namespace std;

uint64_t solve(const uint64_t n, const uint64_t b, const uint64_t y) {
    return n / b - !(n % b) + n / y - !(n % y) - n / lcm(b, y) + !(n % lcm(b, y));
}

int main() {
    uint64_t n, b, y;
    cin >> n >> b >> y;
    cout << solve(n, b, y) << endl;
    return 0;
}