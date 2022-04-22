#include <iostream>
#include <numeric>
#include <string>

using namespace std;
using ll = long long;

string solve(ll x1_1, ll y1_1, ll x2_1, ll y2_1, ll x1_2, ll y1_2, ll x2_2, ll y2_2) {
    ll dx_1 = x2_1 - x1_1, dy_1 = y2_1 - y1_1, dx_2 = x2_2 - x1_2, dy_2 = y2_2 - y1_2;
    ll x_num = dx_1 * dx_2 * (y1_2 - y1_1) + x1_1 * dy_1 * dx_2 - x1_2 * dy_2 * dx_1,
            x_denom = dy_1 * dx_2 - dy_2 * dx_1;
    ll x_d = gcd(x_num, x_denom);
    x_num /= x_d, x_denom /= x_d;
    ll y_num, y_denom;
    if (dx_1)
        y_num = x_num * dy_1 + x_denom * (y1_1 * dx_1 - x1_1 * dy_1), y_denom = x_denom * dx_1;
    else
        y_num = x_num * dy_2 + x_denom * (y1_2 * dx_2 - x1_2 * dy_2), y_denom = x_denom * dx_2;
    ll y_d = gcd(y_num, y_denom);
    y_num /= y_d, y_denom /= y_d;
    if (x_denom < 0)
        x_num *= -1, x_denom *= -1;
    if (y_denom < 0)
        y_num *= -1, y_denom *= -1;
    return to_string(x_num) + '/' + to_string(x_denom) + ' ' + to_string(y_num) + '/' + to_string(y_denom);
}

int main() {
    ll x1_1, y1_1, x2_1, y2_1, x1_2, y1_2, x2_2, y2_2;
    cin >> x1_1 >> y1_1 >> x2_1 >> y2_1 >> x1_2 >> y1_2 >> x2_2 >> y2_2;
    cout << solve(x1_1, y1_1, x2_1, y2_1, x1_2, y1_2, x2_2, y2_2) << endl;
    return 0;
}
/*
0 0
10 0
0 5
10 -5
*/