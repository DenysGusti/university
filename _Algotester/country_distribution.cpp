#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Event {
    int x, y1, y2, type;

    Event(int x, int y1, int y2, int type) : x{x}, y1{y1}, y2{y2}, type{type} {}

    bool operator<(const Event &e) const {
        return x < e.x;
    }

    // Метод для виведення інформації про подію
    void print() const {
        cout << "Event - x: " << x << ", y1: " << y1 << ", y2: " << y2
             << ", type: " << (type == 1 ? "Start" : "End") << '\n';
    }
};

struct SegmentTree {
    vector<int> count, length, coords;

    explicit SegmentTree(const vector<int> &yCoords) :
            count(4 * yCoords.size()), length(4 * yCoords.size()), coords{yCoords} {}

    void update(int node, int start, int end, int l, int r, int val) {
        if (l >= end || r <= start)
            return;
        if (l <= start && r >= end) {
            count[node] += val;
        } else {
            int mid = (start + end) / 2;
            update(2 * node + 1, start, mid, l, r, val);
            update(2 * node + 2, mid, end, l, r, val);
        }

        if (count[node] > 0) {
            length[node] = coords[end] - coords[start];
        } else if (start + 1 == end) {
            length[node] = 0;
        } else {
            length[node] = length[2 * node + 1] + length[2 * node + 2];
        }
    }

    int query() const {
        return length[0];
    }

    void print(int node = 0, int start = 0, int end = -1, int depth = 0) const {
        if (end == -1)
            end = coords.size() - 1;

        // Відступи для кожного рівня дерева
        for (int i = 0; i < depth; ++i) {
            cout << '\t';
        }

        // Виведення інформації про поточний вузол
        cout << "Node: " << node << ", Range: [" << coords[start] << ", " << coords[end] << "], ";
        cout << "Count: " << count[node] << ", Length: " << length[node] << '\n';

        // Якщо це не листовий вузол, рекурсивно вивести дочірні вузли
        if (start + 1 < end) {
            int mid = (start + end) / 2;
            print(2 * node + 1, start, mid, depth + 1);
            print(2 * node + 2, mid, end, depth + 1);
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector <Event> events;
    vector<int> ys;

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.emplace_back(x1, y1, y2, 1);
        events.emplace_back(x2, y1, y2, -1);
        ys.push_back(y1);
        ys.push_back(y2);
    }

    // Координатна компресія
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto getIndex = [&](int y) -> int {
        return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
    };

    // Сортуємо події
    sort(events.begin(), events.end());

    SegmentTree tree{ys};
    uint64_t totalArea = 0;
    int prevX = events[0].x;

    for (const auto &event: events) {
        int currentX = event.x;
        int y1 = getIndex(event.y1);
        int y2 = getIndex(event.y2);

        totalArea += tree.query() * (currentX - prevX);
        tree.update(0, 0, ys.size() - 1, y1, y2, event.type);
        prevX = currentX;
//        event.print();
//        cout << '\n';
//        tree.print();
//        cout << '\n';
    }
    cout << totalArea << '\n';
    return 0;
}
/*
3
0 0 3 3
1 1 4 4
0 2 2 5
*/
