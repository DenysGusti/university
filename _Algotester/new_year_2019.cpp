#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <random>
#include <set>
#include <string>

using namespace std;

struct Point {
    static int64_t det(int64_t a11, int64_t a12, int64_t a21, int64_t a22) {
        return a11 * a22 - a12 * a21;
    }

    // [AB, AC]
    static Point vectorProd(const Point &A, const Point &B, const Point &C) {
        Point a = B - A;
        Point b = C - A;
        return {det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), det(a.x, a.y, b.x, b.y)};
    }

    // vector AB
    static long double lengthVec(const Point &A, const Point &B = {0, 0, 0}) {
        Point vec = B - A;
        return hypot(vec.x, vec.y, vec.z);
    }

    static long double angle(const Point &n1, const Point &n2) {
        long double len_n1 = lengthVec(n1);
        long double len_n2 = lengthVec(n2);
        long double scalar_prod = n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
        if (len_n1 == 0 || len_n2 == 0)
            return 0;
        return acos(scalar_prod / (len_n1 * len_n2));
    }

    int64_t x = 0;
    int64_t y = 0;
    int64_t z = 0;

    Point() = default;

    Point(int64_t x_, int64_t y_, int64_t z_) : x{x_}, y{y_}, z{z_} {}

    auto operator<=>(const Point &) const = default;

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    friend ostream &operator<<(ostream &os, Point &p) {
        os << '(' << p.x << ", " << p.y << ", " << p.z << ')';
        return os;
    }
};

struct Edge {
    int first = -1;
    int second = -1;
    int face_id = -1;
    bool is_close = false;

    Edge(int first_, int second_, int face_id_) : first{first_}, second{second_}, face_id{face_id_} {}
};

struct Face {
    int first = -1;
    int second = -1;
    int third = -1;
    Point normal;

    Face(int first_, int second_, int third_, Point normal_) :
            first{first_}, second{second_}, third{third_}, normal{normal_} {}

    int another(int one, int two) const {
        if ((one == first && two == second) || (one == second && two == first))
            return third;
        if ((one == first && two == third) || (one == third && two == first))
            return second;
        if ((one == third && two == second) || (one == second && two == third))
            return first;
        return -1; // error
    }
};

struct ConvexHull {
    vector<Point> points;
    vector<Face> faces;
    vector<Edge> edges;

    explicit ConvexHull(const vector<Point> &points_) : points{points_} {}

    int findMinZ() const {
        int min_id = 0;
        for (int i = 1; i < points.size(); ++i) {
            if (points[i].z < points[min_id].z ||
                (points[i].z == points[min_id].z && points[i].y < points[min_id].y) ||
                (points[i].z == points[min_id].z && points[i].y == points[min_id].y &&
                 points[i].x < points[min_id].x)) {
                min_id = i;
            }
        }
        return min_id;
    }

    int returnIsEdgeInHull(int a, int b) const {
        for (int i = 0; i < edges.size(); ++i) {
            if ((edges[i].first == a && edges[i].second == b) || (edges[i].first == b && edges[i].second == a)) {
                return i;
            }
        }
        return -1;
    }

    void findFirstFace() {
        int first_point = findMinZ();
        long double min_angle = 7;
        int min_id = -1;
        for (int i = 0; i < points.size(); ++i) {
            if (first_point == i) {
                continue;
            }
            Point &start = points[first_point];
            Point &next = points[i];

            long double angle = Point::angle(start - next, next - Point{next.x, next.y, start.z});

            if (min_angle > angle) {
                min_angle = angle;
                min_id = i;
            }
        }
        int second_point = min_id;

        min_angle = 7;
        min_id = -1;
        for (int i = 0; i < points.size(); ++i) {
            if (first_point == i || second_point == i) {
                continue;
            }
            Point normal = Point::vectorProd(points[first_point], points[second_point], points[i]);
            long double angle = Point::angle(Point{0, 0, 1}, normal);

            if (min_angle > angle) {
                min_angle = angle;
                min_id = i;
            }
        }
        int third_point = min_id;

        Point new_normal = Point::vectorProd(points[first_point], points[second_point], points[third_point]);
        if (new_normal.z > 0) {
            swap(second_point, third_point);
            new_normal = Point::vectorProd(points[first_point], points[second_point], points[third_point]);
        }
        faces.emplace_back(first_point, second_point, third_point, new_normal);
        edges.emplace_back(first_point, second_point, 0);
        edges.emplace_back(second_point, third_point, 0);
        edges.emplace_back(third_point, first_point, 0);
    }

    void makeHull() {
        findFirstFace();
        vector<int> stack = {0, 1, 2};

        while (!stack.empty()) {
            int e_id = stack.back();
            stack.pop_back();
            Edge e = edges[e_id];
            if (e.is_close) {
                continue;
            }
            int min_id = -1;
            long double min_angle = 7;

            Point new_normal;
            int another = faces[e.face_id].another(e.first, e.second);

            for (int i = 0; i < points.size(); ++i) {
                if (i != another && e.first != i && e.second != i) {
//                    cout << e.second << ": " << points[e.second] << ", " << e.first << ": " << points[e.first] << ", "
//                         << i << ": " << points[i] << endl;
                    Point current_normal = Point::vectorProd(points[e.second], points[e.first], points[i]);
                    long double angle = Point::angle(current_normal, faces[e.face_id].normal);

                    if (min_angle > angle) {
                        min_angle = angle;
                        min_id = i;
                        new_normal = current_normal;
                    }
                }
            }
            if (min_id != -1) {
                edges[e_id].is_close = true;
                int first_edge_in_hull = returnIsEdgeInHull(e.first, min_id);
                int second_edge_in_hull = returnIsEdgeInHull(e.second, min_id);

                if (first_edge_in_hull == -1) {
                    edges.emplace_back(e.first, min_id, faces.size());
                    stack.push_back(edges.size() - 1);
                } else {
                    edges[first_edge_in_hull].is_close = true;
                }
                if (second_edge_in_hull == -1) {
                    edges.emplace_back(min_id, e.second, faces.size());
                    stack.push_back(edges.size() - 1);
                } else {
                    edges[second_edge_in_hull].is_close = true;
                }
                faces.emplace_back(e.first, e.second, min_id, new_normal);
            }
        }
    }

    long double calculateSurfaceArea() const {
        long double area = 0;
        for (const auto &face: faces) {
            Point normal = Point::vectorProd(points[face.first], points[face.second], points[face.third]);
            area += Point::lengthVec(normal);
        }
        return area / 2;
    }
};

bool areCoplanar(const Point &P1, const Point &P2, const Point &P3, const Point &P4) {
    // Vector P2 - P1
    long double v1x = P2.x - P1.x;
    long double v1y = P2.y - P1.y;
    long double v1z = P2.z - P1.z;

    // Vector P3 - P1
    long double v2x = P3.x - P1.x;
    long double v2y = P3.y - P1.y;
    long double v2z = P3.z - P1.z;

    // Vector P4 - P1
    long double v3x = P4.x - P1.x;
    long double v3y = P4.y - P1.y;
    long double v3z = P4.z - P1.z;

    // Compute the scalar triple product v1 . (v2 x v3)
    long double scalarTripleProduct = v1x * (v2y * v3z - v2z * v3y) -
                                 v1y * (v2x * v3z - v2z * v3x) +
                                 v1z * (v2x * v3y - v2y * v3x);

    // If the scalar triple product is 0, the points are coplanar
    return abs(scalarTripleProduct) < 1e-9; // Considering floating point precision
}

vector<Point> generateRandomData() {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_int_distribution<> r_n{4, 100};
    uniform_int_distribution<> r_coord{-10'000, 10'000};

    int n = r_n(gen);
    set<Point> data;

    while (data.size() != n) {
        int x = r_coord(gen);
        int y = r_coord(gen);
        int z = r_coord(gen);

        data.emplace(x, y, z);

        vector<Point> tmp{data.begin(), data.end()};
        int sz = tmp.size();

        for (int i = 0; i < sz - 3; ++i) {
            for (int j = i + 1; j < sz - 2; ++j) {
                for (int k = j + 1; k < sz - 1; ++k) {
                    for (int l = k + 1; l < sz; ++l) {
                        if (areCoplanar(tmp[i], tmp[j], tmp[k], tmp[l]))
                            data.erase({x, y, z});
                    }
                }
            }
        }
    }

    return {data.begin(), data.end()};
}

//string runPythonScript(const std::string &command) {
//    string result;
//    char buffer[128];
//    FILE *pipe = _popen(command.c_str(), "r");
//    if (!pipe) {
//        cerr << "popen() failed!" << std::endl;
//        return "";
//    }
//    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
//        result += buffer;
//    }
//    _pclose(pipe);
//    return result;
//}

void test() {
    vector<vector<Point> > tests = {
            {
                    {0, 0, 0},
                    {4, 0, 0},
                    {0, 4, 0},
                    {0, 0, 4},
                    {1, 1, 1},
            },
            {
                    {-10, -8, -7},
                    {-7, -4, 5},
                    {-6, -8, -3},
                    {-6, 7, 1},
                    {-4, -9, 1},
                    {-3, -9, -3},
                    {-3, 0, 0},
                    {2, -10, -8},
                    {3, -3, -6},
                    {4, 7, 5},
                    {7, -8, 5},
                    {8, 8, 9},
                    {10, -6, 0},
                    {10, 0, 6},
                    {10, 0, 9},
            },
    };
    vector<long double> answers = {
            37.856406460551,
            991.4737135450521,
    };

    for (int i = 0; i < tests.size(); ++i) {
        ConvexHull ch{tests[i]};
        ch.makeHull();

        cout << fixed << setprecision(14) << ch.calculateSurfaceArea() << '\n';
        cout << "expected: " << answers[i] << endl;
    }
}

int main() {
    int testing = 2;

    if (testing == 0) {
        vector<Point> points;
        long double ans1 = 0;
        long double ans2 = 0;
        do {
            points = generateRandomData();

            string py_input = "[";
            for (const auto &point: points)
                py_input += format("[{},{},{}],", point.x, point.y, point.z);
            py_input += "]";

//            string output = runPythonScript(
//                    format(R"(python C:\Users\denys\CLionProjects\University\test.py {})", py_input));
//
//            ans1 = stod(output);

            ConvexHull ch{points};
            ch.makeHull();

            ans2 = ch.calculateSurfaceArea();

            cout << "\n{";
            for (const auto &point: points)
                cout << '{' << point.x << ", " << point.y << ", " << point.z << "},\n";
            cout << "},\n";

            cout << fixed << setprecision(14) << ans1 << '\n';
            cout << fixed << setprecision(14) << ans2 << '\n';
            cout << endl;
        } while (abs(ans1 - ans2) <= 1e-7);

    } else if (testing == 1) {
        test();
    } else {
        int n;
        cin >> n;
        vector<Point> points(n);
        for (auto &[x, y, z]: points)
            cin >> x >> y >> z;

        ConvexHull ch{points};
        ch.makeHull();

        cout << fixed << setprecision(14) << ch.calculateSurfaceArea() << '\n';
    }

    return 0;
}

/*
5
0 0 0
4 0 0
0 4 0
0 0 4
1 1 1

15
-10 -8 -7
-7 -4 5
-6 -8 -3
-6 7 1
-4 -9 1
-3 -9 -3
-3 0 0
2 -10 -8
3 -3 -6
4 7 5
7 -8 5
8 8 9
10 -6 0
10 0 6
10 0 9
*/