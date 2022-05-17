#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <array>
#include <vector>
#include <queue>
#include <map>

using namespace std;
using ld = long double;

struct pt {
    ld x{}, y{};

    pt() = default;

    pt(const ld a, const ld b) : x{a}, y{b} {}

    bool operator<(const pt &other) const {
        return this->y != other.y ? this->y < other.y : this->x < other.x;
    }
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

vector<vector<pair<size_t, ld>>> buildGraph(const vector<array<pt, 2>> &gates, const array<pt, 2> &s_and_f) {
    auto &[start, finish] = s_and_f;

    map<pt, size_t> idx;
    idx.emplace(start, 0);
    idx.emplace(finish, gates.size() * 2 + 1);
    size_t i{};
    for (auto &[g1, g2]: gates) {
        idx.emplace(g1, ++i);
        idx.emplace(g2, ++i);
    }

    vector<vector<pair<size_t, ld>>> adj_list((gates.size() + 1) * 2, vector<pair<size_t, ld>>());
    auto dist = [](const pt &p1, const pt &p2) -> ld { return hypot(p1.x - p2.x, p1.y - p2.y); };

    adj_list[idx[start]].emplace_back(idx[gates[0][0]], dist(start, gates[0][0]));
    adj_list[idx[start]].emplace_back(idx[gates[0][1]], dist(start, gates[0][1]));
    adj_list[idx[gates.back()[0]]].emplace_back(idx[finish], dist(gates.back()[0], finish));
    adj_list[idx[gates.back()[1]]].emplace_back(idx[finish], dist(gates.back()[1], finish));

    if (all_of(gates.begin(), gates.end(),
               [&](auto &gate) { return doIntersect(gate[0], gate[1], s_and_f[0], s_and_f[1]); }))
        adj_list[idx[start]].emplace_back(idx[finish], dist(start, finish));

    for (size_t g = 1; g < gates.size(); ++g)
        for (size_t h = 0; h < 2; ++h)
            if (all_of(gates.begin(), gates.begin() + static_cast<vector<pt>::difference_type>(g) + 1,
                       [&](auto &gate) { return doIntersect(gate[0], gate[1], s_and_f[0], gates[g][h]); }))
                adj_list[idx[start]].emplace_back(idx[gates[g][h]], dist(start, gates[g][h]));

    for (size_t g = 0; g < gates.size() - 1; ++g)
        for (size_t h = 0; h < 2; ++h)
            if (all_of(gates.begin() + static_cast<vector<pt>::difference_type>(g), gates.end(),
                       [&](auto &gate) { return doIntersect(gate[0], gate[1], gates[g][h], s_and_f[1]); }))
                adj_list[idx[gates[g][h]]].emplace_back(idx[finish], dist(gates[g][h], finish));


    for (size_t from = 0; from < gates.size() - 1; ++from)
        for (size_t fi = 0; fi < 2; ++fi)
            for (size_t to = from + 1; to < gates.size(); ++to)
                for (size_t ti = 0; ti < 2; ++ti)
                    if (all_of(gates.begin() + static_cast<vector<pt>::difference_type>(from) + 1,
                               gates.begin() + static_cast<vector<pt>::difference_type>(to) + 1, [&](auto &gate) {
                                return doIntersect(gate[0], gate[1], gates[from][fi], gates[to][ti]);
                            }))
                        adj_list[idx[gates[from][fi]]].emplace_back(idx[gates[to][ti]],
                                                                    dist(gates[from][fi], gates[to][ti]));
    return adj_list;
}

ld shortestPath(const vector<vector<pair<size_t, ld>>> &graph) {
    priority_queue<pair<ld, size_t>, vector<pair<ld, size_t>>, greater<>> pq;
    vector<ld> dist(graph.size(), INT16_MAX);
    pq.emplace(0, 0);
    dist[0] = 0;
    for (; !pq.empty(); pq.pop()) {
        size_t u = pq.top().second;
        for (auto &[v, weight]: graph[u])
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
    }
    return dist.back();
}

ld solve(const vector<array<pt, 2>> &gates, const array<pt, 2> &s_and_f) {
    return shortestPath(buildGraph(gates, s_and_f));
}

void tests() {
    auto ans0 = solve({{{{4,  3}, {9,   3}}},
                       {{{-8, 8}, {-13, 8}}}}, {{{0, 0}, {0, 23}}}),
            ans1 = solve({{{{60,  0},   {30, -30}}},
                          {{{50,  -20}, {60, -40}}},
                          {{{80,  -20}, {90, 0}}},
                          {{{100, -30}, {80, -50}}}}, {{{25, 0}, {100, -40}}}),
            ans2 = solve({{{{-4, 2},  {2,  2}}},
                          {{{2,  8},  {-2, 8}}},
                          {{{6,  16}, {2,  14}}},
                          {{{-2, 22}, {0,  20}}}}, {{{0, 0}, {4, 28}}}),
            ans3 = solve({{{{-4,  2},  {2,  2}}},
                          {{{-30, 8},  {20, 8}}},
                          {{{2,   14}, {6,  16}}},
                          {{{4,   20}, {-2, 22}}}}, {{{0, 0}, {24, 28}}}),
            ans4 = solve({{{{0,  1},  {-2, 2}}},
                          {{{7,  -2}, {8,  0}}},
                          {{{10, 0},  {12, -1}}},
                          {{{8,  3},  {9,  5}}},
                          {{{3,  8},  {5,  8}}},
                          {{{2,  10}, {2,  12}}}}, {{{0, 0}, {-3, -12}}}),
            ans5 = solve({{{{-1, 1}, {1, 1}}},
                          {{{-1, 2}, {1, 2}}},
                          {{{-2, 3}, {2, 3}}}}, {{{0, 0}, {0, 10}}}),
            ans6 = solve({{{{-2, 3},  {0, 3}}},
                          {{{3,  4},  {2, 6}}},
                          {{{3,  8},  {5, 8}}},
                          {{{0,  10}, {0, 12}}}}, {{{0, 0}, {-4, 12}}}),
            ans7 = solve({{{{-3, 2}, {-1, 2}}},
                          {{{0,  3}, {0,  5}}},
                          {{{3,  6}, {5,  6}}},
                          {{{1,  8}, {1,  10}}}}, {{{0, 0}, {0, 13}}}),
            ans8 = solve({{{{-1, 1}, {0,  1}}},
                          {{{0,  2}, {1,  2}}},
                          {{{-2, 3}, {-1, 3}}},
                          {{{7,  4}, {8,  4}}}}, {{{0, 0}, {7, 5}}}),
            ans9 = solve({{{{1, 1}, {2, 1}}}}, {{{0, 0}, {0, 2}}});

    cout << boolalpha << fixed << setprecision(3) <<
         "\ntest 0: " << (abs(ans0 - 35.000) < 1e-3) << "\tgot: " << ans0 << "\texpected: " << 35.000 <<
         "\ntest 1: " << (abs(ans1 - 90.300) < 1e-3) << "\tgot: " << ans1 << "\texpected: " << 90.300 <<
         "\ntest 2: " << (abs(ans2 - 29.411) < 1e-3) << "\tgot: " << ans2 << "\texpected: " << 29.411 <<
         "\ntest 3: " << (abs(ans3 - 41.937) < 1e-3) << "\tgot: " << ans3 << "\texpected: " << 41.937 <<
         "\ntest 4: " << (abs(ans4 - 46.448) < 1e-3) << "\tgot: " << ans4 << "\texpected: " << 46.448 <<
         "\ntest 5: " << (abs(ans5 - 10.000) < 1e-3) << "\tgot: " << ans5 << "\texpected: " << 10.000 <<
         "\ntest 6: " << (abs(ans6 - 16.919) < 1e-3) << "\tgot: " << ans6 << "\texpected: " << 16.919 <<
         "\ntest 7: " << (abs(ans7 - 15.527) < 1e-3) << "\tgot: " << ans7 << "\texpected: " << 15.527 <<
         "\ntest 8: " << (abs(ans8 - 12.476) < 1e-3) << "\tgot: " << ans8 << "\texpected: " << 12.476 <<
         "\ntest 9: " << (abs(ans9 - 2.828) < 1e-3) << "\tgot: " << ans9 << "\texpected: " << 2.828 << endl;
}

int main() {
    size_t n;
    cin >> n;
    vector<array<pt, 2>> gates(n);
    array<pt, 2> s_and_f;
    for (auto &[p, q]: gates)
        cin >> p.x >> p.y >> q.x >> q.y;
    for (auto &p: s_and_f)
        cin >> p.x >> p.y;

    cout << fixed << setprecision(3) << solve(gates, s_and_f) << endl;
//    tests();
    return 0;
}

/*
2
4 3 9 3
-8 8 -13 8
0 0
0 23
*/
