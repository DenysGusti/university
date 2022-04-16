#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> parent;
int cycle_start, cycle_end;

bool dfs(int v, int par) { // passing vertex and its parent vertex
    visited[v] = true;
    for (int u: adj[v]) {
        if (u == par) continue; // skipping edge to parent vertex
        if (visited[u]) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, parent[u]))
            return true;
    }
    return false;
}

void find_cycle() {
    visited.assign(n, false);
    parent.assign(n, -1);
    cycle_start = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v]))
            break;
    }

    if (cycle_start == -1) {
//        cout << "Acyclic" << endl;
    } else {
//        vector<int> cycle = {cycle_start};
        set<int> cycle = {cycle_start};
        for (int v = cycle_end; v != cycle_start; v = parent[v])
//            cycle.push_back(v);
            cycle.insert(v);
//        cycle.push_back(cycle_start);
//        reverse(cycle.begin(), cycle.end());

//        cout << "Cycle found: ";
        cout << cycle.size() << '\n';
        for (int v: cycle)
            cout << v + 1 << ' ';
        cout << endl;
    }
}

int main() {
    cin >> n;
    adj.assign(n, vector<int>());
    for (int tmp1, tmp2, i = 0; i < n; ++i) {
        cin >> tmp1 >> tmp2;
        adj[tmp1 - 1].push_back(tmp2 - 1);
        adj[tmp2 - 1].push_back(tmp1 - 1);
    }
    find_cycle();
    return 0;
}
/*
4
1 2
2 3
3 4
4 2
*/
