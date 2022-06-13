#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>

using namespace std;

struct Event {
    int64_t x{}, y{};
    bool type{};     // 0 for start and 1 for end
    size_t index{};    // index in the rect array

    Event(const int64_t a, const int64_t b, const bool t, const size_t id) : x{a}, y{b}, type{t}, index{id} {}
};

int64_t findDeltaY(const vector<bool> &is_active, const vector<array<int64_t, 4>> &rect) {
    vector<Event> e;
    e.reserve(2 * rect.size());
    for (size_t i = -1; const auto &rec: rect)
        if (is_active[++i]) { // insert the active rectangle's start and end into an array
            e.emplace_back(rec[0], rec[1], 0, i);
            e.emplace_back(rec[2], rec[3], 1, i);
        }

    ranges::sort(e, {}, &Event::y);

    size_t cnt{}; // number of active rectangles in y direction
    // this is what we are here to find, dy = sigma (end-begin),we will iterate and try to find these begin and end
    int64_t dy{}, begin{};
    for (const auto &ev: e)
        if (!ev.type) {
            if (!cnt)
                begin = ev.y;
            ++cnt;
        } else {
            --cnt;
            if (!cnt)
                dy += (ev.y - begin); // when cnt is 0, we have reached a boundary
        }
    return dy;
}

uint64_t rectangleArea(const vector<array<int64_t, 4>> &rect) {
    uint64_t ans{};
    vector<Event> e;
    e.reserve(2 * rect.size());
    for (size_t i = -1; const auto &rec: rect) {
        e.emplace_back(rec[0], rec[1], 0, ++i);
        e.emplace_back(rec[2], rec[3], 1, i);
    }

    ranges::sort(e, {}, &Event::x); // sorted according to x coordinate as we are going to traverse from left to right
    vector<bool> is_active(rect.size());

    for (int64_t prev{}, delta_x, delta_y; const auto &it: e) {
        if (&it == &e.front())
            prev = it.x;
        else { // all the trouble is just for finding these two values
            delta_x = it.x - prev; // just the difference between previous x coordinate and this one
            delta_y = findDeltaY(is_active, rect);
            prev = it.x;
            ans += delta_x * delta_y;
        }
        is_active[it.index] = it.type == 0; // insert into active rectangles, remove from active rectangles;
    }
    return ans;
}

uint64_t minArea(const vector<array<int64_t, 4>> &rect) {
    int64_t x1{}, y1{}, x2{}, y2{};
    for (const auto &el: rect) {
        x1 = min(x1, el[0]);
        y1 = min(y1, el[1]);
        x2 = max(x2, el[2]);
        y2 = max(y2, el[3]);
    }
    return (x2 - x1) * (y2 - y1);
}

int main() {
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\tasks\sheets.txt)"};
    size_t n{};
    fin >> n;
    vector<array<int64_t, 4>> arr;
    arr.reserve(n);
    for (int a, b, c, d, i = 0; i < n; ++i) {
        fin >> a >> b >> c >> d;
        arr.push_back({a, b, c, d});
    }

    cout << "Rectangles:\n";
    for (const auto &el: arr)
        cout << el[0] << ' ' << el[1] << ' ' << el[2] << ' ' << el[3] << '\n';
    cout << "Minimal area of a rectangle, which covers all rectangles: " << minArea(arr) <<
         "\nOverall area, covered by rectangles: " << rectangleArea(arr) << endl;
    return 0;
}