#include <iostream>

using namespace std;
typedef unsigned long long ull;

ull double_fact_loop(const int &n) {
    ull f = 1;
    for (int i = n; i > 0; i -= 2) f *= i;
    return f;
}

ull double_fact_recursion(const int &n) {
    if (n < 2) return 1;
    return n * double_fact_recursion(n - 2);
}

int main() {
    int n;
    cin >> n;
    cout << n << "!! = " << double_fact_loop(n) << " or " << double_fact_recursion(n);
    return 0;
}