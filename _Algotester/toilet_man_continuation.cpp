#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int n, k, x1, y1, x2, y2;
    cin >> n >> k >> x1 >> y1 >> x2 >> y2;
    vector<int> lr(2 * n);
    for (auto &point: lr)
        cin >> point;

    double x_intersect = static_cast<double>((0 - y1) * (x2 - x1)) / (y2 - y1) + x1;
    double dist = 0;
    // closest right point idx
    ptrdiff_t crp_idx = lower_bound(lr.begin(), lr.end(), x_intersect) - lr.begin();
    if (k == 1) {
        if (crp_idx % 2 == 1) { // inside gate
            dist = hypot(x2 - x1, y2 - y1);
        } else {     // closest point
            if (crp_idx == 0) { // intersection on the left of gates
                dist = hypot(lr.front() - x1, 0 - y1) + hypot(lr.front() - x2, 0 - y2);
            } else if (crp_idx == lr.size()) { // intersection on the right of gates
                dist = hypot(lr.back() - x1, 0 - y1) + hypot(lr.back() - x2, 0 - y2);
            } else {
                int x_closest =
                        x_intersect - lr[crp_idx - 1] < lr[crp_idx] - x_intersect ? lr[crp_idx - 1] : lr[crp_idx];
                dist = hypot(x_closest - x1, 0 - y1) + hypot(x_closest - x2, 0 - y2);
            }
        }
    } else {
        ptrdiff_t step = 2 * k - 3;
        if (crp_idx == 0) { // intersection on the left of gates
            int x_l = lr.front();
            int x_r = lr[step + 1]; // one more than optimal
            dist = min(hypot(x_l - x1, 0 - y1) + hypot(x_r - x2, 0 - y2),
                       hypot(x_l - x2, 0 - y2) + hypot(x_r - x1, 0 - y1)) + x_r - x_l;
        } else if (crp_idx == lr.size()) { // intersection on the right of gates
            int x_l = lr.end()[-step - 2];   // one more than optimal
            int x_r = lr.back();
            dist = min(hypot(x_l - x1, 0 - y1) + hypot(x_r - x2, 0 - y2),
                       hypot(x_l - x2, 0 - y2) + hypot(x_r - x1, 0 - y1)) + x_r - x_l;
        } else {
            dist = numeric_limits<double>::max();
            for (size_t i = 1; i + step < lr.size(); i += 2) {
                int x_l = lr[i];
                int x_r = lr[i + step];
                double n_dist = min(hypot(x_l - x1, 0 - y1) + hypot(x_r - x2, 0 - y2),
                                    hypot(x_l - x2, 0 - y2) + hypot(x_r - x1, 0 - y1)) + x_r - x_l;
                dist = min(dist, n_dist);
            }
        }
    }
    cout << setprecision(13) << dist << '\n';
    return 0;
}
/*
2 1
0 5
0 -5
-5 -3
3 5

2 2
0 5
0 -5
-5 -3
3 5
*/
