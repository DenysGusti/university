#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <chrono>
#include <print>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Rectangle {
    int x1, y1, x2, y2;

    bool doIntersect(const Rectangle &r) const {
        return max(x1, r.x1) < min(x2, r.x2) && max(y1, r.y1) < min(y2, r.y2);
    }

    bool noOtherIntersect(const Rectangle &r, const vector <Rectangle> &rects) const {
        for (const auto &rect: rects) {
            if (&rect == this || &rect == &r)
                continue;
            if (rect.doIntersect(*this) || rect.doIntersect(r))
                return false;
        }
        return true;
    }

    bool operator<(const Rectangle &r) const {
        return x1 < r.x1;
    }
};

class Timer {
    using clock = chrono::steady_clock;

private:
    clock::time_point startTimePoint;
    string message;

public:
    explicit Timer(const string_view msg) : startTimePoint{clock::now()}, message{msg} {}

    [[nodiscard]] auto elapsed() const {
        return chrono::duration_cast<chrono::milliseconds>(clock::now() - startTimePoint);
    }

    void reset() {
        startTimePoint = clock::now();
    }

    ~Timer() {
        println("{}: elapsed time [H:M:S]: {:%T}", message, elapsed());
    }
};

vector <Rectangle> generateRandomData() {
    random_device rd;
    mt19937_64 gen{rd()};
    uniform_int_distribution<> r_n{2, 10'000};
    uniform_int_distribution<> r_coord{0, 1'000'000};

    int n = r_n(gen);
    vector <Rectangle> data;

    for (int i = 0; i < n; ++i) {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        while (x1 >= x2) {
            x1 = r_coord(gen);
            x2 = r_coord(gen);
        }
        while (y1 >= y2) {
            y1 = r_coord(gen);
            y2 = r_coord(gen);
        }
        data.emplace_back(x1, y1, x2, y2);
    }
    return data;
}

int solver1(const vector <Rectangle> &rects) {
    Timer t{"naive"};
    int count = 0;
    for (int i = 0; i < rects.size(); ++i) {
        for (int j = i + 1; j < rects.size(); ++j) {
            if (rects[i].doIntersect(rects[j]) && rects[i].noOtherIntersect(rects[j], rects)) {
                ++count;
            }
        }
    }
    return count;
}

struct Event {
    int x, y1, y2, type, index;

    bool operator<(const Event &other) const {
        if (x != other.x) return x < other.x;
        return type < other.type;
    }

    void print() const {
        cout << "Event - x: " << x << ", y1: " << y1 << ", y2: " << y2
             << ", type: " << (type == 1 ? "Start" : "End") << '\n';
    }
};

struct SegmentTree {
    vector<int> full_cover_group;
    vector<int> full_cover_count;
    vector<int> group;
    int new_group_idx = 0;
    vector <unordered_map<int, int>> partial_cover_groups;
    unordered_map<int, unordered_set<int> > group_rect_ids;
    unordered_map<int, unordered_set<int> > full_cover_group_nodes;
    unordered_map<int, unordered_set<int> > partial_cover_group_nodes;

    explicit SegmentTree(size_t n, size_t r_s) :
            full_cover_count(4 * n),
            full_cover_group(4 * n, -1),
            partial_cover_groups(4 * n),
            group(r_s, -1) {}

    void update(int node, int start, int end, int l, int r, int type, int id) {
        if (type == 1) {
            ++partial_cover_groups[node][group[id]];
            if (partial_cover_groups[node][group[id]] == 1) {
                partial_cover_group_nodes[group[id]].insert(node);
            }
        } else {
            --partial_cover_groups[node][group[id]];
            if (partial_cover_groups[node][group[id]] == 0) {
                partial_cover_group_nodes[group[id]].erase(node);
                partial_cover_groups[node].erase(group[id]);
            }
        }

        if (l <= start && r >= end) {
            if (type == 1) {
                ++full_cover_count[node];
                if (full_cover_count[node] == 1) {
                    full_cover_group[node] = group[id];
                    full_cover_group_nodes[full_cover_group[node]].insert(node);
                }
            } else {
                --full_cover_count[node];
                if (full_cover_count[node] == 0) {
                    full_cover_group_nodes[full_cover_group[node]].erase(node);
                    full_cover_group[node] = -1;
                }
            }
        } else {
            int mid = (start + end) / 2;
            if (l < mid) {
                update(2 * node + 1, start, mid, l, r, type, id);
            }
            if (r > mid) {
                update(2 * node + 2, mid, end, l, r, type, id);
            }
        }
    }

    void mergeGroups(int group_to, int group_from) {
        if (group_to == group_from) {
            cout << "!!!" << endl;
        }
        for (int node_id: full_cover_group_nodes[group_from])
            full_cover_group[node_id] = group_to;
        full_cover_group_nodes[group_to].merge(full_cover_group_nodes[group_from]);
        full_cover_group_nodes.erase(group_from);

        for (int node_id: partial_cover_group_nodes[group_from]) {
            partial_cover_groups[node_id][group_to] += partial_cover_groups[node_id][group_from];
            partial_cover_groups[node_id].erase(group_from);
        }
        partial_cover_group_nodes[group_to].merge(partial_cover_group_nodes[group_from]);
        partial_cover_group_nodes.erase(group_from);

        for (int rect_id: group_rect_ids[group_from])
            group[rect_id] = group_to;
        group_rect_ids[group_to].merge(group_rect_ids[group_from]);
        group_rect_ids.erase(group_from);
    }

    void queue(int node, int start, int end, int l, int r, int id) {
        if (full_cover_group[node] != -1) {
            int this_group = group[id];
            int other_group = full_cover_group[node];
            if (this_group == -1) {
                group[id] = other_group;
                group_rect_ids[other_group].insert(id);
            } else if (this_group != other_group) {
                mergeGroups(this_group, other_group);
            }
        } else if (l <= start && r >= end) {
            if (!partial_cover_groups[node].empty()) {
                int this_group = group[id];
                int other_group = partial_cover_groups[node].begin()->first;
                if (partial_cover_groups[node].size() == 1) {
                    if (this_group == -1) {
                        group[id] = other_group;
                        group_rect_ids[other_group].insert(id);
                    } else if (this_group != other_group) {
                        mergeGroups(this_group, other_group);
                    }
                } else {
                    unordered_set<int> groups_to_merge;
                    groups_to_merge.reserve(partial_cover_groups[node].size());
                    for (auto [other_group_partial, counter]: partial_cover_groups[node]) {
                        groups_to_merge.insert(other_group_partial);
                    }
                    if (this_group == -1) {
                        group[id] = other_group;
                        this_group = other_group;
                        group_rect_ids[other_group].insert(id);
                    }
                    groups_to_merge.erase(this_group);
                    for (int group_to_merge: groups_to_merge) {
                        mergeGroups(this_group, group_to_merge);
                    }
                }
            }
        } else {
            int mid = (start + end) / 2;
            int left_child_node = 2 * node + 1;
            int right_child_node = 2 * node + 2;
            if (l < mid && !partial_cover_groups[left_child_node].empty()) {
                queue(left_child_node, start, mid, l, r, id);
            }
            if (r > mid && !partial_cover_groups[right_child_node].empty()) {
                queue(right_child_node, mid, end, l, r, id);
            }
        }
    }

    void add_group(int id) {
        if (group[id] == -1) {
            group[id] = new_group_idx++;
            group_rect_ids[group[id]].insert(id);
        }
    }

    void print(int node = 0, int start = 0, int end = -1, int depth = 0) const {
        if (end == -1)
            end = full_cover_group.size() / 4 - 1;

        for (int i = 0; i < depth; ++i) {
            cout << '\t';
        }

        cout << "Node: " << node << ", Range: [" << start << ", " << end << "], ";
        cout << "Full Cover Count: " << full_cover_count[node] << ", ";
        cout << "Full Cover Group: " << full_cover_group[node] << ", ";
        cout << "Partial Cover: [";
        for (const auto [i, counter]: partial_cover_groups[node])
            cout << '(' << i << ", " << counter << "), ";
        cout << "]\n";

        if (start + 1 < end) {
            int mid = (start + end) / 2;
            print(2 * node + 1, start, mid, depth + 1);
            print(2 * node + 2, mid, end, depth + 1);
        }
        if (node == 0) {
            cout << "Group: [";
            for (int i = 0; i < group.size(); ++i) {
                cout << '(' << i << ", " << group[i] << "), ";
            }
            cout << "]\n";

            cout << "Group Rect Ids: [";
            for (const auto &[i, gr]: group_rect_ids) {
                cout << i << ": {";
                for (auto j: gr) {
                    cout << j << ", ";
                }
                cout << "}, ";
            }
            cout << "]\n";

            cout << "Full Cover Group Nodes: [";
            for (const auto &[i, gr]: full_cover_group_nodes) {
                cout << i << ": {";
                for (auto j: gr) {
                    cout << j << ", ";
                }
                cout << "}, ";
            }
            cout << "]\n";

            cout << "Partial Cover Group Nodes: [";
            for (const auto &[i, gr]: partial_cover_group_nodes) {
                cout << i << ": {";
                for (auto j: gr) {
                    cout << j << ", ";
                }
                cout << "}, ";
            }
            cout << "]\n";
        }
    }
};

int solver2(const vector <Rectangle> &rects) {
//    Timer t{"optimized"};

    set<int> s_xs, s_ys;

    for (const auto &rect: rects) {
        s_xs.insert(rect.x1);
        s_xs.insert(rect.x2);
        s_ys.insert(rect.y1);
        s_ys.insert(rect.y2);
    }

    vector <Event> events;

    vector<int> xs{s_xs.begin(), s_xs.end()}, ys{s_ys.begin(), s_ys.end()};

    for (int i = 0; i < rects.size(); ++i) {
        int x1_idx = lower_bound(xs.begin(), xs.end(), rects[i].x1) - xs.begin();
        int x2_idx = lower_bound(xs.begin(), xs.end(), rects[i].x2) - xs.begin();
        int y1_idx = lower_bound(ys.begin(), ys.end(), rects[i].y1) - ys.begin();
        int y2_idx = lower_bound(ys.begin(), ys.end(), rects[i].y2) - ys.begin();
        events.emplace_back(x1_idx, y1_idx, y2_idx, 1, i);
        events.emplace_back(x2_idx, y1_idx, y2_idx, -1, i);
    }

    sort(events.begin(), events.end());

    SegmentTree tree{static_cast<size_t>(ys.size()), rects.size()};
    for (const auto &event: events) {
        if (event.type == 1) {
            tree.queue(0, 0, ys.size() - 1, event.y1, event.y2, event.index);
            tree.add_group(event.index);
        }
        tree.update(0, 0, ys.size() - 1, event.y1, event.y2, event.type, event.index);

//        event.print();
//        tree.print();
//        cout << '\n' << endl;
    }

    int ans = 0;
    for (const auto &[group, group_rects]: tree.group_rect_ids) {
        if (group_rects.size() == 2)
            ++ans;
    }
    return ans;
}

void stresstest() {
    vector <Rectangle> rects;
    int ans1 = 0, ans2 = 0;

    do {
        rects = generateRandomData();

        ans1 = solver1(rects);
        ans2 = solver2(rects);
        cout << ans1 << ' ' << ans2 << endl;
    } while (ans1 == ans2);

    cout << rects.size() << '\n';

    for (const auto &rect: rects)
        cout << rect.x1 << ' ' << rect.y1 << ' ' << rect.x2 << ' ' << rect.y2 << '\n';

    cout << ans1 << ' ' << ans2 << '\n';
}

vector <Rectangle> generateFinalTest() {
    vector <Rectangle> result;
    int n = 100'000;
    result.reserve(n);
    for (int i = 0; i < n / 2; ++i) {
        result.emplace_back(2 * i, 0, 2 * i + 1, n);
    }
    for (int i = 0; i < n / 2; ++i) {
        result.emplace_back(0, 2 * i, n, 2 * i + 1);
    }
    return result;
}

void test() {
    vector <vector<Rectangle>> tests = {
            {
                    {0, 0, 2, 2},
                    {1, 1, 3, 3},
                    {4, 7, 7, 11}
            },
            {
                    {0, 0, 2, 2},
                    {1, 1, 3, 3},
                    {2, 2, 4, 4}
            },
            {
                    {0, 1, 2, 2},
                    {1, 0, 2, 1}
            },
            {
                    {0, 0, 2, 1},
                    {0, 2, 2, 3},
                    {1, 0, 3, 1},
                    {1, 2, 3, 3},
                    {2, 0, 3, 3}
            },
            {
                    {0, 0, 2, 1},
                    {1, 0, 3, 1}
            },
            {
                    {0, 0, 1, 2},
                    {0, 0, 2, 2},
                    {3, 1, 4, 3}
            },
            {
                    {2, 2, 3, 3},
                    {2, 1, 3, 4},
                    {1, 2, 3, 3},
                    {0, 0, 4, 2},
                    {3, 0, 5, 1}
            },
            {
                    {1, 0, 3, 2},
                    {2, 1, 3, 3},
                    {1, 2, 3, 4}
            },
            {
                    {1, 0, 3, 1},
                    {0, 2, 2, 3},
                    {2, 0, 3, 4}
            },
            {
                    {2, 1, 3, 3},
                    {0, 0, 1, 2},
                    {0, 2, 1, 3},
                    {0, 2, 1, 3}
            },
            {
                    {0, 1, 4, 2},
                    {1, 0, 2, 3},
                    {2, 0, 4, 2},
                    {0, 2, 2, 4},
                    {2, 1, 3, 5}
            },
            {
                    {1, 1, 5, 3},
                    {0, 0, 2, 1},
                    {2, 0, 5, 1},
                    {1, 0, 2, 2},
                    {2, 0, 5, 5}
            },
            {
                    {2, 1, 5, 5},
                    {1, 2, 5, 4},
                    {1, 4, 5, 5},
                    {1, 2, 3, 3},
                    {0, 0, 4, 2}
            },
            {
                    {0, 3, 2, 4},
                    {1, 4, 3, 5},
                    {1, 0, 5, 4},
                    {1, 1, 5, 5},
                    {1, 1, 5, 5}
            },
            {
                    {1, 1, 4, 5},
                    {1, 0, 4, 2},
                    {0, 3, 3, 5},
                    {2, 3, 3, 5},
                    {0, 0, 4, 3}
            },
            generateFinalTest()
    };

    for (const auto &rects: tests) {
        int ans1 = solver1(rects);
        int ans2 = solver2(rects);

        if (ans1 != ans2) {
            cout << rects.size() << '\n';

            for (const auto &rect: rects)
                cout << rect.x1 << ' ' << rect.y1 << ' ' << rect.x2 << ' ' << rect.y2 << '\n';

            cout << ans1 << ' ' << ans2 << '\n';
        }
        cout << endl;
    }
}

void input_rects() {
    int n;
    cin >> n;
    vector <Rectangle> rects(n);
    for (auto &rect: rects) {
        cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;
    }
    cout << solver2(rects) << '\n';
}

int main() {
    input_rects();
//    stresstest();
//    test();
    return 0;
}
