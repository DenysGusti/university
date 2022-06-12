#include <iostream>

using namespace std;

int findLast(int n, int p) { // 1..n
    if (n == 1)
        return 1;
    return (findLast(n - 1, p) + p - 1) % n + 1;
}

int main() {
    int n, p;
    cout << "n, p = ";
    cin >> n >> p;
    cout << findLast(n, p) << endl;
    return 0;
}