#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int main() {
    int n, v;
    cin >> n >> v;
    vector<pair<int, int>> points(n);
    for (auto &[x, y]: points)
        cin >> x >> y;
    points.emplace_back();  // Add starting point (0,0) implicitly
    ++n;

    vector<vector<float> > graph(n, vector<float>(n));
    vector<vector<float> > dp(n, vector<float>(1 << n, numeric_limits<float>::max()));

    // Calculate distances between all pairs of points
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            float dist = hypot(points[i].first - points[j].first, points[i].second - points[j].second);
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }

    // Initialize dp table for base cases
    for (int i = 0; i < n; ++i) {
        dp[i][1 << i | 1] = graph[0][i];
    }

    // Iterate over all masks
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // If it is included in the set represented by mask
                for (int j = 0; j < n; ++j) {
                    if (j != i && (mask & (1 << j))) { // If j is included and is different from i
                        dp[i][mask] = min(dp[i][mask], dp[j][mask ^ (1 << i)] + graph[j][i]);
                    }
                }
            }
        }
    }

    float ans = numeric_limits<float>::max();

    // Find the minimum cost to return to the starting point
    for (int i = 1; i < n; ++i) {
        ans = min(ans, dp[i][(1 << n) - 1] + graph[i][0]);
    }

    cout << ans / v << '\n';

    return 0;
}


/*
3 4
1 4
-2 7
-1 -1

4.4605544059

20 1
-85 423
317 -726
-503 398
216 563
-721 240
924 -184
663 902
-451 712
580 -641
-387 198
704 516
-322 -373
870 -512
123 734
-960 -99
456 -455
-644 802
988 357
-116 -796
587 650

7795.52
*/
