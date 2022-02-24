#include <iostream>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    long int a[m];
    for (int i = 0; i < m; i++) cin >> a[i];
    long int l = 0;
    int o = 0;
    for (auto i: a) {
        if (l + i <= k) {
            l += i;
        } else {
            o++;
            l = i;
        }
    }
    if (l <= k) o++;
    cout << max(-1, n - o);
    return 0;
}