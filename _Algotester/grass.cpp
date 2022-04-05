#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n, k, res = INT16_MAX;
    string tmp;
    cin >> n >> k;
    vector<vector<int>> field(n, vector<int>(n));
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, INT16_MAX)));
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        for (int j = 0; j < n; ++j)
            field[i][j] = tmp[j] - '0';
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            dp[i][j][0] = 0;
            dp[i][j][field[i][j]] = min(1, dp[i][j][field[i][j]]);
            for (int s = 0; s <= k; ++s) {
                if (s == k)
                    res = min(dp[i][j][s], res);
                if (i < n - 1)
                    dp[i + 1][j][min(s + field[i + 1][j], k)] =
                            min(dp[i + 1][j][min(s + field[i + 1][j], k)], dp[i][j][s] + 1);
                if (j < n - 1)
                    dp[i][j + 1][min(s + field[i][j + 1], k)] =
                            min(dp[i][j + 1][min(s + field[i][j + 1], k)], dp[i][j][s] + 1);
            }
        }
    if (res == INT16_MAX)
        res = -1;
    cout << res << endl;
    return 0;
}
/*
4 3
0101
0001
0100
0001
*/