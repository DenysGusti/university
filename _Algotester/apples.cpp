#include <iostream>
//////////////////////////////////
int n, m;
using namespace std;

void apples(double x, int y) {
    if (y >= m) {
        --y;
        return;
    }
    if (x == int(x)) apples(x / 2, ++y);
    if (y == n) cout << x << " ";
    apples(x - 0.5, ++y);
}

int main() {
    cin >> n >> m;
    apples(n, 0);
    return 0;
}