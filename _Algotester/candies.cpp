#include <iostream>
#include <algorithm>

using namespace std;
typedef long long int ll;
typedef long double ld;

void calcsubarray(const ll a[], ll x[], const int &n, const int &c) {
    for (int i = 0; i < (1 << n); ++i) {
        ll s = 0;
        for (int j = 0; j < n; ++j) if (i & (1 << j)) s += a[j + c];
        x[i] = s;
    }
}

ll solvesubsetsum(ll a[], const int &n, const ld &average) {
    int first = n / 2, second = n - n / 2, size_X = 1 << (n / 2), size_Y = 1 << (n - n / 2);
    ll X[size_X], Y[size_Y];
    calcsubarray(a, X, first, 0);
    calcsubarray(a, Y, second, first);
    sort(Y, Y + size_Y);
//    cout << "average = " << average << '\n';
//    for (int i = 0; i < size_X; ++i) cout << X[i] << ' ';
//    cout << '\n';
//    for (int j = 0; j < size_Y; ++j) cout << Y[j] << ' ';
    ll less = 0, more = 2e9;
    for (auto i: X) {
        ld ith_average = average - i;
        auto p = lower_bound(Y, Y + size_Y, ith_average) - Y, t = upper_bound(Y, Y + size_Y, ith_average) - Y;
//            cout << "\n\nX[] = " << i << "\nbefore: pY[" << p << "] = " << Y[p] << "\ttY[" << t << "] = "
//                 << Y[t];
        if (p == size_Y || Y[p] != ith_average) --p;
        if (t == size_Y || (Y[t - 1] >= ith_average && t)) --t;
        if (Y[p] <= ith_average) less = max(less, Y[p] + i);
        if (Y[t] >= ith_average) more = min(more, Y[t] + i);
//            cout << "\nafter: pY[" << p << "] = " << Y[p] << "\ttY[" << t << "] = " << Y[t] << "\nlower = " << less
//                 << "\tupper = " << more << '\n';
    }
    return more - less;
}

int main() {
    int n;
    cin >> n;
    ll w[n];
    ld sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        sum += (ld) w[i];
    }
    cout << solvesubsetsum(w, n, sum / 2) << endl;
    return 0;
}
/*
5
5 8 13 27 14
5
27 14 13 8 5
5
8 14 13 27 8
5
13 27 14 8 9
5
50 5 14 8 27
2
3 1
3
7 6 1
*/
