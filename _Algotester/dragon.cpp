#include <iostream>

using namespace std;

int main() {
    short int n, m;
    cin >> n >> m;
    char a[n][m];
    for (short int i = 0; i < n * m; ++i) cin >> *(*a + i);
    for (short int i = 0; i < n; ++i)
        for (short int j = 0; j < m; ++j) {
            bool flag = false;
            for (short int x = 0; x < n; ++x)
                if (x != i && a[x][j] == a[i][j]) {
                    flag = true;
                    break;
                }
            for (short int y = 0; y < m; ++y)
                if (y != j && a[i][y] == a[i][j]) {
                    flag = true;
                    break;
                }
            if (!flag) cout << a[i][j];
        }
    return 0;
}