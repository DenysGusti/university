#include <iostream>

using namespace std;

int main() {
    const size_t n = 10;
    double arr[n];

    for (bool finish = false; !finish;) {
        try {
            for (size_t i = 0; i < n; ++i) {
                if (!(cin >> arr[i]))
                    throw logic_error("enter numbers");
                else if (i == n - 1)
                    finish = true;
            }
        } catch (const logic_error &e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    }

    cout << "Input:\n";
    for (size_t i = 0; i < n; ++i)
        cout << arr[i] << ' ';

    bool flag = true;
    for (size_t i = 0; i < n - 1; ++i)
        if (arr[i] * arr[i + 1] >= 0) {
            flag = false;
            break;
        }
    cout << "\nOutput:\nsigns of values " << (flag ? "" : "don't ") << "alternate" << endl;
    return 0;
}

// 1 -2 3 -4 5 -6 7 -8 9 -10