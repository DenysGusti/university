#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

vector<vector<uint64_t> > adj, adj_rev;
vector<bool> used;
vector<uint64_t> order, component;

void dfs1(int v) {
    used[v] = true;

    for (auto u: adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u: adj_rev[v])
        if (!used[u])
            dfs2(u);
}

void solve() {
    size_t n{}, m{};
    cin >> n >> m;
//    cout << n << ' ' << m << endl;
    adj.assign(n, {});
    adj_rev.assign(n, {});

    for (size_t a{}, b{}, i = 0; i < m; ++i) {
        cin >> a >> b;
//        cout << a << ' ' << b << endl;
        adj[a - 1].push_back(b - 1);
        adj_rev[b - 1].push_back(a - 1);
    }

    used.assign(n, false);

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    used.assign(n, false);
    reverse(order.begin(), order.end());

    size_t counter{};

    for (auto v: order)
        if (!used[v]) {
            dfs2(v);

//            cout << "here" << endl;
            ++counter;

            component.clear();
        }

    adj.clear();
    adj_rev.clear();
    used.clear();
    order.clear();

//    cout <<  "eop: " << counter << endl;

    if (counter == 1)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

int main() {
    size_t t{};
    for (cin >> t; t; --t)
        solve();
    return 0;
}
