#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    long long x;
    cin >> n >> m >> x;
    long long a[n], b[m];
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int j = 0; j < m; ++j) cin >> b[j];
#define sarr ((n <= m) ? a : b)
#define barr ((n <= m) ? b : a)
#define slen min(n, m)
#define blen max(n, m)
    sort(barr, barr + blen);
    long long min_diff = 1e18;
    for (int i = 0; i < slen; ++i) {
        long long diff = max((long long) 1, x - sarr[i]);
        if (!diff) continue;
        int l = 0, r = blen - 1;
        while (l < r - 1) {
            int mid = (l + r) / 2;
            ((barr[mid] < diff) ? l : r) = mid;
        }
        min_diff = min({min_diff, abs(x - sarr[i] - barr[l]), abs(x - sarr[i] - barr[r])});
    }
    cout << min_diff << endl;
    return 0;
}
/*
4 3 7
1 4 2 10
7 3 8
0
2 2 7
4 3
7 2
1
*/