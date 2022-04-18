#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

void shortestPath(vector<vector<pair<int, int>>> &adj, int n, int src, int comp) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(n, INT32_MAX >> 1);
    pq.emplace(0, src);
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto &x: adj[u]) {
            auto &[v, weight] = x;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }
    cout << count_if(dist.begin(), dist.end(), [&](auto el) { return el <= comp; }) << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n * n);
    for (int tmp, i{}, j{}, cur = 0; cur < n * n && cin >> tmp; ++cur, i = cur / n, j = cur % n) {
        if (i)
            adj[cur - n].emplace_back(cur, tmp);
        if (n - i - 1)
            adj[cur + n].emplace_back(cur, tmp);
        if (j)
            adj[cur - 1].emplace_back(cur, tmp);
        if (n - j - 1)
            adj[cur + 1].emplace_back(cur, tmp);
        if (!(i || j))
            m -= tmp;
    }
    shortestPath(adj, n * n, 0, m);
    return 0;
}
/*
2 2
1 1
1 1

5 37
9 6 6 7 1
9 9 3 5 3
10 1 9 7 9
3 1 6 9 9
5 6 9 1 9

5 15
1 1 1 1 1
20 20 20 20 1
1 1 1 20 1
20 20 1 20 1
20 20 1 1 1
*/
