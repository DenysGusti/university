#include <iostream>
#include <limits>

using namespace std;

int main() {
    /*
    cout << boolalpha << numeric_limits<long double>::max() << endl;
    for (int i = 0, j = 10; j >= i; ++i, --j) {
        cout << i << " " << j << endl;
    }
    int arr[] = {1, 2, 3, 4, 5};
    for (auto a: arr) {
        cout << a << endl;
    }
    int n = 2;
    switch (n) {
        case 1:
            cout << "one";
            break;
        case 2:
            cout << "two";
            break;
        default:
            cout << "other";
    }
     */

    int n;
    cin >> n;
    for (int i = n; i > 0; i -= 2) {
        for (int j = 0; j < (n - i) / 2; ++j) cout << ' ';
        for (int j = 0; j < i; ++j) cout << '*';
        cout << endl;
    }
    /*
    int d = 2;
    while (n > 1) {
        if (n % d == 0) {
            cout << d << " ";
            n /= d;
        } else {
            d++;
        }
    }
     */
    return 0;
}