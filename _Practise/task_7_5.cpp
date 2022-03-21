#include <iostream>

using namespace std;

void print_table(const int &n);

int main() {
    int n;
    cin >> n;
    print_table(n);
    return 0;
}

void print_table(const int &n) {
    for (int j = 2; j <= 2 * n; j += 2)
        for (int i = j; i <= 2 * (n - 1) + j; i += 2)
            cout << (i - 1) % (2 * n) + 1 << (i < 2 * (n - 1) + j ? '\t' : '\n');
}