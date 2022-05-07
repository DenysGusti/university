#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;

struct pt {
    ll x, y;

    pt(const ll a, const ll b) : x{a}, y{b} {}

    bool operator<(const pt &other) const {
        return this->y != other.y ? this->y < other.y : this->x < other.x;
    }
};

int orientation(const pt &a, const pt &b, const pt &c) {
    ll v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return v != 0 ? (v > 0 ? +1 : -1) : 0;
}

vector<pt> convex_hull(vector<pt> &a) {
    auto p0 = *min_element(a.begin(), a.end());
    sort(a.begin(), a.end(), [&p0](const pt &c, const pt &d) {
        int o = orientation(p0, c, d);
        return o == 0 ? hypot(p0.x - c.x, p0.y - c.y) < hypot(p0.x - d.x, p0.y - d.y) : o < 0;
    });
    vector<pt> st;
    st.reserve(a.size() + 1);
    for (const auto &point: a) {
        while (st.size() > 1 && orientation(st.rbegin()[1], st.back(), point) >= 0)
            st.pop_back();
        st.emplace_back(point);
    }
    return st;
}

ll count_int_points(const pt &p, const pt &q) {
    return gcd(abs(p.x - q.x), abs(p.y - q.y)) - 1;
}

int main() {
    size_t n;
    cin >> n;
    vector<pt> points;
    points.reserve(n);
    for (ll x, y, i = 0; i < n; ++i) {
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    auto shell = convex_hull(points);
    ll ans = shell.size();
    for (int i = 0; i < shell.size(); ++i)
        ans += count_int_points(shell[i], shell[(i + 1) % shell.size()]);
    cout << ans << endl;
    return 0;
}
/*
3
0 0
2 0
0 2

4
0 0
2 0
0 2
2 2

13
-11 0
0 0
5 0
13 0
5 4
-2 4
-1 7
1 11
5 12
-2 12
0 -12
6 -12
11 -9
*/
