#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int s;
    cin >> s;

    if (s % 2 == 0) {
        cout << s / 2;
    } else {
        if (s < 9) {
            cout << 1;
        } else if (s == 9) {
            cout << 3;
        } else {
            cout << (s - 9) / 2 + 2;
        }
    }
}

