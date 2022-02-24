#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long int n, k, res = 100000;
    cin >> n >> k;
    for (int i = 1; i < 100000; ++i) res = min(min(n % i, i - n % i) + abs(k - i), res);
    cout << res;
    return 0;
}
// 2757 37 2754/34=81
// 18 6
// 9512 145 9514/142=67
// 9 5