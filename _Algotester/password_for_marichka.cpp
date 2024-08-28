#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int lenN(int n) {
    int len = 0;
    for (; n > 0; n /= 10) {
        ++len;
    }
    return len;
}

int main() {
    int l, r, lenl, lenr;
    cin >> l >> r;
    lenl = lenN(l);
    lenr = lenN(r);

    if (lenl == lenr) {
        cout << l;
    } else {
        int answ = 10;
        for (int i = 1; i < lenl; ++i) {
            answ *= 10;
        }
        if (l * 10 == answ)
            cout << l;
        else {
            cout << answ;
        }
    }
}

