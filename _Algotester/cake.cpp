#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) cin >> *(a + i);
    sort(a, a + n);
    double res = a[0];
    for (int i = 1; i < n; ++i) res = (res + a[i]) / 2;
    printf("%.7lf", res);
    return 0;
}