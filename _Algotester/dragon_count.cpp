#include <iostream>
#include <vector>

#define p 1000000007
typedef unsigned long long ull;

ull catalan(ull n) {
    std::vector<ull> catalan_arr(n + 1);
    catalan_arr[0] = catalan_arr[1] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            catalan_arr[i] = (catalan_arr[i] + catalan_arr[j] * catalan_arr[i - j - 1]) % p;
    return catalan_arr[n];
}

ull bin_pow_mod(ull x, ull y) {
    ull res = 1;
    while (y) {
        if (y & 1) res = res * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return res;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::cout << catalan(n) * bin_pow_mod(k, n) % p << std::endl;
    return 0;
}