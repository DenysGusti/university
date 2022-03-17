#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int xl, xr, r, n;

void find_virtual_pillars(vector<pair<int, int>> &arr) {
    vector<pair<int, int>> temporary;
    const int l_x_center = xl - r, r_x_center = xr + r;
    for(auto &i: arr) {
        bool left_flag = true, right_flag = true;
        auto &[x_i, y_i] = i;
        for (auto &j: arr) {
            if (i != j) {
                auto &[x_j, y_j] = j;
                if (left_flag && hypot((l_x_center + x_i) / 2.0 - x_j, y_i - y_j) <= abs(l_x_center - x_i) / 2.0)
                    left_flag = false;
                if (right_flag && hypot((r_x_center + x_i) / 2.0 - x_j, y_i - y_j) <= abs(r_x_center - x_i) / 2.0)
                    right_flag = false;
            }
        }
        if (left_flag) temporary.emplace_back(l_x_center, y_i);
        if (right_flag) temporary.emplace_back(r_x_center, y_i);
    }
    arr.insert(arr.end(), temporary.begin(), temporary.end());
}

int main() {
    double d{};
    // input
    cin >> xl >> xr >> r >> n;
    vector<pair<int, int>> pillars;
    for (int x, y, i = 0; i < n; ++i) {
        cin >> x >> y;
        pillars.emplace_back(x, y);
    }
    // virtual
    find_virtual_pillars(pillars);
    for(auto &[x, y]: pillars)  cout << x << ' ' << y << '\n';
    cout << pillars.size() << '\n';
    cout << d - 2 * r << endl;
    return 0;
}
/*
0 90
3
4
10 10
70 10
50 50
10 90
*/