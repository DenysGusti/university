#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int h, H, s;

    cin >> h >> H >> s;

    double root = hypot(s, h);
    double result = H / h * root + (H % h) * root / h;

    cout << result << endl;
}
