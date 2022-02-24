#include <iostream>
#include <cmath>

using namespace std;

int main() {
    short int k;
    double x1, x2, x3, y1, y2, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> k;
    char turn;
    for (int i = 0; i < k; ++i) cin >> turn;
    double s = abs((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)) / 2.0;
    printf("%.7lf", s / pow(2, k));
    return 0;
}