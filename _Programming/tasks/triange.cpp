#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
using ld = long double;

pair<ld, ld> getCoords(const uint64_t n) {
    uint64_t level = 0, shift = n - 1;
    for (; (level + 1) * (level + 2) / 2 < n; ++level, shift -= level) {}
    return {-static_cast<ld>(level) / 2 + static_cast<ld>(shift),
            static_cast<ld>(level) * sin(static_cast<ld>(M_PI) / 3)};
}

int main() {
    pair<ld, ld> points[3];
    for (size_t tmp, i = 0; i < 3; ++i) {
        cin >> tmp;
        points[i] = getCoords(tmp);
    }

    bool right = true;
    for (size_t i = 0; i < 3; ++i)
        if (abs(hypot(points[i].first - points[(i + 1) % 3].first, points[i].second - points[(i + 1) % 3].second) -
                hypot(points[(i + 1) % 3].first - points[(i + 2) % 3].first,
                      points[(i + 1) % 3].second - points[(i + 2) % 3].second)) >= 1e-7) {
            right = false;
            break;
        }

    ld p{};
    for (size_t i = 0; i < 3; ++i)
        p += hypot(points[i].first - points[(i + 1) % 3].first, points[i].second - points[(i + 1) % 3].second);

    cout << boolalpha << "Triangle is equilateral: " << right <<
         "\nPerimeter: " << fixed << setprecision(4) << p << endl;
    return 0;
}

/*
1 2 3
2 3 5
4 5 6
2 16 20
10 19 8
22 28 2
22 28 85
23 27 61
*/

