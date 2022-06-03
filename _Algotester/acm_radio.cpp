#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <cmath>
#include <tuple>

using namespace std;
using ld = long double;

struct pt {
    ld x{}, y{}, phi{};

    pt() = default;

    pt(const ld a, const ld b) : x{a}, y{b}, phi{atan2(b, a)} {}
};

bool doIntersect(const pt &p1, const pt &q1, const pt &p2, const pt &q2) {
    auto onSegment = [](const pt &p, const pt &q, const pt &r) -> bool {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
    };

    auto orientation = [](const pt &p, const pt &q, const pt &r) -> int {
        ld val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        return (val == 0) ? 0 : (val > 0) ? 1 : -1;
    };

    int o1 = orientation(p1, q1, p2), o2 = orientation(p1, q1, q2),
            o3 = orientation(p2, q2, p1), o4 = orientation(p2, q2, q1);
    return (o1 != o2 && o3 != o4) || (o1 == 0 && onSegment(p1, p2, q1)) || (o2 == 0 && onSegment(p1, q2, q1)) ||
           (o3 == 0 && onSegment(p2, p1, q2)) || (o4 == 0 && onSegment(p2, q1, q2));
}

pt findIntersection(const pt &a1, const pt &b1, const pt &a2, const pt &b2) {
    ld d = (a1.x - b1.x) * (a2.y - b2.y) - (a1.y - b1.y) * (a2.x - b2.x);
    return {((a1.x * b1.y - a1.y * b1.x) * (a2.x - b2.x) - (a1.x - b1.x) * (a2.x * b2.y - a2.y * b2.x)) / d,
            ((a1.x * b1.y - a1.y * b1.x) * (a2.y - b2.y) - (a1.y - b1.y) * (a2.x * b2.y - a2.y * b2.x)) / d};
}

void norm(pt &a, pt &b) {
    if (abs(a.phi - b.phi) > M_PI) {
        if (a.phi < 0)
            a.phi += 2 * M_PI;
        else if (b.phi < 0)
            b.phi += 2 * M_PI;
    }
    if (a.phi < 0 || b.phi < 0) {
        a.phi += 2 * M_PI;
        b.phi += 2 * M_PI;
    }
    if (a.phi > b.phi && abs(a.phi - b.phi) > M_PI)
        b.phi += 2 * M_PI;
}

tuple<ld, ld, ld> abc(const pt &p, const pt &q) {
    return {q.y - p.y, p.x - q.x, p.y * (q.x - p.x) - p.x * (q.y - p.y)};
}

pair<pt, pt> circleIntersect(ld r, ld a, ld b, ld c) {
    if (c * c > r * r * (a * a + b * b))
        return {{0, 0},
                {0, 0}};
    ld x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    ld d = r * r - c * c / (a * a + b * b), mult = sqrt(d / (a * a + b * b));
    ld ax = x0 + b * mult, bx = x0 - b * mult, ay = y0 - a * mult, by = y0 + a * mult;
    return {{ax, ay},
            {bx, by}};
}

void cutOutsideCircle(const ld r, vector<array<pt, 2>> &segments) {
    for (auto &seg: segments) {
        if (hypot(seg[0].x, seg[0].y) > r && hypot(seg[1].x, seg[1].y) > r) {
            auto [a, b, c] = abc(seg[0], seg[1]);
            auto [p, q] = circleIntersect(r, a, b, c);
            if (hypot(seg[0].x - seg[1].x, seg[0].y - seg[1].y) < hypot(p.x - q.x, p.y - q.y))
                seg = {{{0, 0}, {0, 0}}};
            else {
                seg[0] = p;
                seg[1] = q;
                norm(seg[0], seg[1]);
                if (seg[0].phi > seg[1].phi)
                    swap(seg[0], seg[1]);
            }
        } else if (hypot(seg[0].x, seg[0].y) > r && hypot(seg[1].x, seg[1].y) < r) {
            auto [a, b, c] = abc(seg[0], seg[1]);
            auto [p, q] = circleIntersect(r, a, b, c);
            pt m = {(seg[0].x + seg[1].x) / 2, (seg[0].y + seg[1].y) / 2};
            if (hypot(m.x - p.x, m.y - p.y) < (hypot(m.x - q.x, m.y - q.y)))
                seg[0] = p;
            else if (hypot(m.x - p.x, m.y - p.y) > (hypot(m.x - q.x, m.y - q.y)))
                seg[0] = q;
        } else if (hypot(seg[0].x, seg[0].y) < r && hypot(seg[1].x, seg[1].y) > r) {
            auto [a, b, c] = abc(seg[0], seg[1]);
            auto [p, q] = circleIntersect(r, a, b, c);
            pt m = {(seg[0].x + seg[1].x) / 2, (seg[0].y + seg[1].y) / 2};
            if (hypot(m.x - p.x, m.y - p.y) < (hypot(m.x - q.x, m.y - q.y)))
                seg[1] = p;
            else if (hypot(m.x - p.x, m.y - p.y) > (hypot(m.x - q.x, m.y - q.y)))
                seg[1] = q;
        }
        norm(seg[0], seg[1]);
    }
}

void cutInsideCircle(const ld r, vector<array<pt, 2>> &segments) {
    for (auto &seg1: segments)
        for (auto &seg2: segments)
            if ((seg1[0].x != seg2[0].x || seg1[0].y != seg2[0].y) &&
                (seg1[0].x != 0 || seg1[0].y != 0) && (seg2[0].x != 0 || seg2[0].y != 0)) {
                if (abs(seg1[0].phi - seg2[0].phi) < 1e-6 && abs(seg1[1].phi - seg2[1].phi) < 1e-6) {
                    pt m{(seg2[0].x + seg2[1].x) / 2, (seg2[0].y + seg2[1].y) / 2};
                    if (doIntersect(seg1[0], seg1[1], {r * cos(m.phi), r * sin(m.phi)}, m)) {
                        seg1 = {{{0, 0}, {0, 0}}};
                    }
                } else if (doIntersect(seg1[0], seg1[1], {r * cos(seg2[0].phi), r * sin(seg2[0].phi)}, seg2[0]) ||
                           doIntersect(seg1[0], seg1[1], {r * cos(seg2[1].phi), r * sin(seg2[1].phi)}, seg2[1])) {
                    if (seg1[0].phi < seg2[0].phi - 1e-6 && seg2[0].phi < seg1[1].phi - 1e-6 &&
                        seg1[0].phi < seg2[1].phi - 1e-6 && seg2[1].phi < seg1[1].phi - 1e-6 ||
                        seg1[0].phi - 2 * M_PI < seg2[0].phi - 1e-6 && seg2[0].phi < seg1[1].phi - 2 * M_PI - 1e-6 &&
                        seg1[0].phi - 2 * M_PI < seg2[1].phi - 1e-6 && seg2[1].phi < seg1[1].phi - 2 * M_PI - 1e-6 ||
                        seg1[0].phi + 2 * M_PI < seg2[0].phi - 1e-6 && seg2[0].phi < seg1[1].phi + 2 * M_PI - 1e-6 &&
                        seg1[0].phi + 2 * M_PI < seg2[1].phi - 1e-6 && seg2[1].phi < seg1[1].phi + 2 * M_PI - 1e-6) {
                        segments.emplace_back(array<pt, 2>{{findIntersection(
                                seg1[0], seg1[1], {r * cos(seg2[1].phi), r * sin(seg2[1].phi)}, seg2[1]), seg1[1]}});
                        seg1[1] = findIntersection(seg1[0], seg1[1],
                                                   {r * cos(seg2[0].phi), r * sin(seg2[0].phi)}, seg2[0]);
                        norm(segments.back()[0], segments.back()[1]);
                        norm(seg1[0], seg1[1]);
                    } else if (seg1[0].phi < seg2[0].phi + 1e-6 && seg2[0].phi < seg1[1].phi - 1e-6 ||
                               seg1[0].phi - 2 * M_PI < seg2[0].phi - 1e-6 &&
                               seg2[0].phi < seg1[1].phi - 2 * M_PI - 1e-6 ||
                               seg1[0].phi + 2 * M_PI < seg2[0].phi - 1e-6 &&
                               seg2[0].phi < seg1[1].phi + 2 * M_PI - 1e-6) {
                        seg1[1] = findIntersection(seg1[0], seg1[1],
                                                   {r * cos(seg2[0].phi), r * sin(seg2[0].phi)}, seg2[0]);
                        norm(seg1[0], seg1[1]);
                    } else if (seg1[0].phi < seg2[1].phi + 1e-6 && seg2[1].phi < seg1[1].phi - 1e-6 ||
                               seg1[0].phi - 2 * M_PI < seg2[1].phi - 1e-6 &&
                               seg2[1].phi < seg1[1].phi - 2 * M_PI - 1e-6 ||
                               seg1[0].phi + 2 * M_PI < seg2[1].phi - 1e-6 &&
                               seg2[1].phi < seg1[1].phi + 2 * M_PI - 1e-6) {
                        seg1[0] = findIntersection(seg1[0], seg1[1],
                                                   {r * cos(seg2[1].phi), r * sin(seg2[1].phi)}, seg2[1]);
                        norm(seg1[0], seg1[1]);
                    }
                }
            }
}

ld solve(const ld r, vector<array<pt, 2>> &segments) {
    cutOutsideCircle(r, segments);
    cutInsideCircle(r, segments);

    for (auto &seg1: segments)
        for (auto &seg2: segments)
            if (abs(seg1[0].phi - seg2[0].phi) > 1e-6 || abs(seg1[1].phi - seg2[1].phi) > 1e-6)
                if (seg1[0].phi <= seg2[0].phi + 1e-6 && seg2[1].phi <= seg1[1].phi + 1e-6 ||
                    seg1[0].phi + 2 * M_PI <= seg2[0].phi + 1e-6 && seg2[1].phi <= seg1[1].phi + 2 * M_PI + 1e-6 ||
                    seg1[0].phi - 2 * M_PI <= seg2[0].phi + 1e-6 && seg2[1].phi <= seg1[1].phi - 2 * M_PI + 1e-6) {
                    seg2 = {{{0, 0}, {0, 0}}};
                }

    ld s{}, angle = 2 * M_PI;
    for (auto &seg: segments) {
        angle -= seg[1].phi - seg[0].phi;
        s += (seg[0].x * seg[1].y - seg[1].x * seg[0].y) / 2;
    }
    s += angle * r * r / 2;
    return s;
}


int main() {
    ld r;
    size_t n;
    cin >> r >> n;
    vector<array<pt, 2>> segments;
    segments.reserve(2 * n);
    for (int a, b, c, d, i = 0; i < n; ++i) {
        cin >> a >> b >> c >> d;
        segments.emplace_back(
                array<pt, 2>{{{static_cast<ld>(a), static_cast<ld>(b)}, {static_cast<ld>(c), static_cast<ld>(d)}}});
        norm(segments.back()[0], segments.back()[1]);
        if (segments.back()[0].phi > segments.back()[1].phi)
            swap(segments.back()[0], segments.back()[1]);
    }
    cout << fixed << setprecision(3) << solve(r, segments) << endl;
    return 0;
}

/*
5 4
1 -2 3 4
23 32 4 1
-6 2 -5 1
2 3 -2 2
ans: 45.942

5 4
-1 2 3 -1
3 4 -3 2
5 4 3 -7
6 8 2 1
ans: 46.719

5 2
-1 0 0 1
0 -5 5 0
ans: 52.270

5 2
-1 -1 -1 1
1 -1 1 1
ans: 41.270

9 14
-8 2 -2 8
-6 3 -5 4
-4 5 -3 6
2 5 5 3
0 3 2 3
3 2 3 1
-1 -2 1 -2
-3 0 -2 -2
-3 -2 -1 -3
-1 -4 3 -5
-1 -5 -5 0
-3 -6 3 -6
-4 -6 -6 1
4 0 7 0
ans: 116.795

5 4
-3 1 1 2
-4 2 -2 -4
1 4 3 -2
-2 -3 4 -2
ans: 23.672

5 4
-2 2 1 2
1 3 2 -2
-2 -3 3 -2
-2 -4 -3 3
ans: 19.786

5 4
-1 1 1 1
2 2 2 -2
-2 -3 3 -3
-3 3 -2 -4
ans: 20.441

5 1
5 0 7 0
ans: 78.540

5 1
-5 4 1 -7
ans: 62.960
*/