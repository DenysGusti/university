#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <tuple>
#include <random>
#include <string>

using namespace std;
using ll = long long;

auto normalize(int a, int b, int c) {
    int d = gcd(gcd(a, b), c);
    a /= d, b /= d, c /= d;
    if (a < 0)
        a *= -1, b *= -1, c *= -1;
    else if (a == 0 && b < 0)
        b *= -1, c *= -1;
    return make_tuple(a, b, c);
}

auto parallel_families(set<tuple<int, int, int>> &lines) {
    set<pair<int, int>> normals;
    vector<int> families;
    families.reserve(lines.size());
    for (const auto &[a, b, c]: lines) {
        int d = gcd(a, b);
        normals.emplace(a / d, b / d);
    }

/*    cout << "normals: " << normals.size() << '\n';
    for (const auto &[a, b]: normals)
        cout << a << ' ' << b << '\n';*/

    for (const auto &[a, b]: normals) {
        int counter{};
        for (const auto &[al, bl, cl]: lines){
            int dl = gcd(al, bl);
            if (al / dl == a && bl /dl == b)
                counter++;
        }
        if (counter >= 2)
            families.push_back(counter);
    }

/*    cout << "families: " << families.size() << '\n';
    for (const auto &el: families)
        cout << el << '\n';*/

    return families;
}

auto multiple_points(set<tuple<int, int, int>> &lines) {
    set<tuple<ll, ll, ll, ll>> points;
    vector<int> multiples;
    multiples.reserve(lines.size());

    for (const auto &line1: lines)
        for (const auto &line2: lines)
            if (line1 < line2) {
                const auto &[a1, b1, c1] = line1;
                const auto &[a2, b2, c2] = line2;
                if (a1 * b2 - a2 * b1) {
//                    cout << a1 << ' ' << b1 << ' ' << c1 << '\t' << a2 << ' ' << b2 << ' ' << c2 << '\n';
                    ll x_num = b1 * c2 - b2 * c1, x_denom = a1 * b2 - a2 * b1;
                    ll x_d = gcd(x_num, x_denom);
                    x_num /= x_d, x_denom /= x_d;
                    ll y_num, y_denom;
                    if (b1)
                        y_num = -(a1 * x_num + c1 * x_denom), y_denom = b1 * x_denom;
                    else
                        y_num = -(a2 * x_num + c2 * x_denom), y_denom = b2 * x_denom;
                    ll y_d = gcd(y_num, y_denom);
                    y_num /= y_d, y_denom /= y_d;
                    if (x_denom < 0)
                        x_num *= -1, x_denom *= -1;
                    if (y_denom < 0)
                        y_num *= -1, y_denom *= -1;
//                    cout << x_num << '/' << x_denom << ' ' << y_num << '/' << y_denom << "\n\n";
                    points.emplace(x_num, x_denom, y_num, y_denom);
                }
            }

/*    cout << "points: " << points.size() << '\n';
    for (const auto &[x_num, x_denom, y_num, y_denom]: points)
        cout << x_num << '/' << x_denom << ' ' << y_num << '/' << y_denom << '\n';*/

    for (const auto &[x_num, x_denom, y_num, y_denom]: points) {
        int counter{};
        for (const auto &[a, b, c]: lines)
            if (!(a * x_num * y_denom + b * y_num * x_denom + c * x_denom * y_denom))
                counter++;
        if (counter >= 3)
            multiples.push_back(counter);
    }

/*    cout << "multiples: " << multiples.size() << '\n';
    for (const auto &el: multiples)
        cout << el << '\n';*/

    return multiples;
}

int solve(int n, vector<int> &mp, vector<int> &pf) {
    auto c_2_k = [](const int k) { return k * (k - 1) / 2; };

    int max_slices = 1 + n + c_2_k(n);
//    cout << "max_slices: " << max_slices << '\n';

    int loss_mp = accumulate(mp.begin(), mp.end(), 0, [&](int i, int j) { return i + c_2_k(j - 1); });
//    cout << "loss_mp: " << loss_mp << '\n';

    int loss_pf = accumulate(pf.begin(), pf.end(), 0, [&](int i, int j) { return i + c_2_k(j); });
//    cout << "loss_pf: " << loss_pf << '\n';

    int ans = max_slices - loss_mp - loss_pf;
//    cout << "ans: " << ans << '\n';

    return ans;
}

void test() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<size_t> size_dist(1, 10);
    uniform_int_distribution<int> abc_dist(-1, 1);
    const int n_tests = 10;
    for (int i = 0; i < n_tests; ++i) {
        cout << "test " << i + 1 << "\n\n";
        string s{};
        size_t n = size_dist(gen);
        cout << n << '\n';
        set<tuple<int, int, int>> lines;
        for (int a, b, c, j = 0; j < n; ++j) {
            a = abc_dist(gen), b = abc_dist(gen), c = abc_dist(gen);
            cout << a << ' ' << b << ' ' << c << '\n';
            s += to_string(a) + "x+" + to_string(b) + "y+" + to_string(c) + "=0\n";
            if (a || b)
                lines.emplace(normalize(a, b, c));
        }
        auto pf = parallel_families(lines);
        auto mp = multiple_points(lines);
        cout << '\n' << solve(static_cast<int>(lines.size()), mp, pf) << '\n';
        cout << '\n' << s << endl;
    }
}

int main() {
    size_t n;
    cin >> n;
    set<tuple<int, int, int>> lines;
    for (int a, b, c, i = 0; i < n; ++i) { // ax+by+c=0
        cin >> a >> b >> c;
        if (a || b)
            lines.emplace(normalize(a, b, c));
    }

//    cout << "lines: " << lines.size() << '\n';
//    for (const auto &[a, b, c]: lines)
//        cout << a << ' ' << b << ' ' << c << '\n';

    auto pf = parallel_families(lines);
    auto mp = multiple_points(lines);

    cout << solve(static_cast<int>(lines.size()), mp, pf) << endl;
//    test();
    return 0;
}
/*
3
1 0 0
0 1 0
-1 -1 1

10
1 2 3
2 4 6
3 9 27
-3 9 27
-3 -9 -27
0 -2 18
0 1 9
0 -1 -9
1 1 1
1 -1 1

3
1 0 0
2 0 -1
3 0 1

3
1 2 0
2 4 -1
3 6 1
*/