#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int a, b, c, D;
    cout << "a, b, c: ";
    cin >> a >> b >> c;
    if (a == 0) {
        cout << "linear";
    } else {
        D = b * b - 4 * a * c;
        if (D > 0) {
            double x1, x2;
            x1 = (-b + sqrt(D)) / (2 * a);
            x2 = (-b - sqrt(D)) / (2 * a);
            cout << x1 << " " << x2;
        } else if (D == 0) {
            double x;
            x = -b / double(2 * a);
            cout << x;
        } else {
            cout << "not real";
        }
        return 0;
    }
}
