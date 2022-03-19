#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
typedef pair<int, int> xy_pair;
typedef vector<xy_pair> xy_vector;
typedef map<xy_pair, double> xy_map;

xy_vector find_virtual_pillars(xy_vector &arr, const xy_pair &borders) {
    xy_vector l_virtual, temp;
    auto &[lx_center, rx_center] = borders;
    for (const auto &i: arr) {
        bool left_flag = true, right_flag = true;
        auto &[x_i, y_i] = i;
        for (auto &j: arr) {
            if (i != j) {
                const auto &[x_j, y_j] = j;
                if (left_flag && hypot((lx_center + x_i) / 2.0 - x_j, y_i - y_j) <= abs(lx_center - x_i) / 2.0)
                    left_flag = false;
                if (right_flag && hypot((rx_center + x_i) / 2.0 - x_j, y_i - y_j) <= abs(rx_center - x_i) / 2.0)
                    right_flag = false;
            }
        }
        if (left_flag) l_virtual.emplace_back(lx_center, y_i);
        if (right_flag) temp.emplace_back(rx_center, y_i);
    }
    arr.insert(arr.end(), temp.begin(), temp.end());
    return l_virtual;
}

double dist_to_pillar_from_graph(const xy_vector &arr, const xy_pair &p) {
    double d = numeric_limits<double>::max();
    auto &[p_x, p_y] = p;
    for (const auto &[g_x, g_y]: arr) d = min(d, hypot(p_x - g_x, p_y - g_y));
    return d;
}

xy_pair nearest_pillar(const xy_map &d_to_xy) {
    xy_pair p;
    auto d = numeric_limits<double>::max();
    for (const auto &[m_p, m_d]: d_to_xy)
        if (m_d < d) {
            d = m_d;
            p = m_p;
        }
//    cout << p.first << ' ' << p.second << ' ' << d << '\n';
    return p;
}

double find_d_with_graph(xy_vector &graph, xy_vector &queue, const xy_pair &borders) {
    double d{};
    xy_map dist_to_xy;
    while (true) {
        // init
        for (const auto &i: queue) dist_to_xy[i] = dist_to_pillar_from_graph(graph, i);
//        for (const auto &[p, dist]: dist_to_xy) cout << '(' << p.first << ", " << p.second << "): " << dist << '\n';
        // build
        auto key = nearest_pillar(dist_to_xy);
        d = max(d, dist_to_xy[key]);
        dist_to_xy.erase(key);
        graph.push_back(key);
        queue.erase(find(queue.begin(), queue.end(), key));
        if (key.first == borders.second) break;
    }
    return d;
}

int main() {
    int xl, xr, r, n;
    // input
    cin >> xl >> xr >> r >> n;
    xy_vector pillars(n);
    xy_pair borders(xl - r, xr + r);
    for (auto &[x, y]: pillars) cin >> x >> y;
    // virtual
    auto core = find_virtual_pillars(pillars, borders);
//    for (const auto &[x, y]: pillars) cout << x << ' ' << y << '\n';
//    for (const auto &[x, y]: core) cout << x << ' ' << y << '\n';
//    cout << pillars.size() + core.size() << '\n';
    // graph
    auto d = find_d_with_graph(core, pillars, borders);
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