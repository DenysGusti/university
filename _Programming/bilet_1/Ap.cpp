#include <iostream>

using namespace std;

int main() {
    const size_t n = 9;
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

    double min_el = arr[0], max_el = arr[0];
    for (size_t i = 0; i < n; ++i) {
        min_el = min(arr[i], min_el);
        max_el = max(arr[i], max_el);
    }

    cout << "Input:\n";
    for (size_t i = 0; i < n; ++i)
        cout << arr[i] << (i < n - 1 ? ' ' : '\n');
    cout << "Output:\n" << max_el - min_el << endl;
    return 0;
}

// 1 -2 3 -4 5 -6 7 -8 9