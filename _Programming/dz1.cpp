#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    // cout << max({a, b, c});
    int max_n = a;
    if (max_n < b) {
        max_n = b;
    }
    if (max_n < c) {
        max_n = c;
    }
    cout << max_n;
    return 0;
}