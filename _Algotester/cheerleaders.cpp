#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k, z, result = 0;
    cin >> n >> k >> z;
    vector<int> a(n);

    for (auto &e: a) {
        cin >> e;
    }

    sort(a.begin(), a.end());

    for (auto &e: a) {
        if (2 * e <= z) {
            z -= 2 * e;
            result++;
        } else {
            break;
        }
    }

    cout << min(result, k) << endl;
}
