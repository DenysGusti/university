#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


using namespace std;

void dfsf(int v, vector<bool> &v_used, vector<vector<int>> &adj_lst, int &sum) {
    v_used[v] = true; //in general, i can just pop them, then no need to find unvisited
    for (auto el: adj_lst[v]) {
        sum++;
        if (!v_used[el]) {
            dfsf(el, v_used, adj_lst, sum);
        }
    }
}

int main() {
    int n{}, m{};
    int tmp1, tmp2;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        cin >> tmp1 >> tmp2;
        a[tmp1 - 1].push_back(tmp2 - 1);
        a[tmp2 - 1].push_back(tmp1 - 1);
    }
    vector<bool> used(n);
    vector<int> sizes;
    stack<int> dfs;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            // cout << i << ": " << endl;
            dfs.push(i);
            int tmp3{};
            while (!dfs.empty()) {
                int j = dfs.top();
                dfs.pop();
                if (!used[j]) {
                    used[j] = true;
                    for (auto &node: a[j]) {
                        // cout << node << endl;
                        dfs.push(node);
                        ++tmp3;
                    }
                }
            }
            sizes.push_back(tmp3 / 2);
            // cout << "size: " << tmp3 << endl;
        }
    }
    sort(sizes.begin(), sizes.end());
    cout << sizes.size() << '\n';
    for (auto &el: sizes)
        cout << el << '\n';
    return 0;
}
/*
6 5
1 2
2 3
4 5
2 1
3 1

3 2
1 3
2 3
*/
