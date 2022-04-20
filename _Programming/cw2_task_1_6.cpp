#include <iostream>

using namespace std;

// Злити 2 посортованих динамічних цілочислових масиви в один посортований.
// Не використовувати додаткового сортування.

int main() {
    int n1, n2, n3;

    cout << "Enter size of 1st array: ";
    cin >> n1;
    auto arr1 = new int[n1];
    cout << "Enter 1st array: ";
    for (int i = 0; i < n1; ++i)
        cin >> arr1[i];
    for (int i = 0; i < n1; ++i)
        cout << arr1[i] << (i < n1 - 1 ? ' ' : '\n');

    cout << "Enter size of 2nd array: ";
    cin >> n2;
    auto arr2 = new int[n2];
    cout << "Enter 2nd array: ";
    for (int i = 0; i < n2; ++i)
        cin >> arr2[i];
    for (int i = 0; i < n2; ++i)
        cout << arr2[i] << (i < n2 - 1 ? ' ' : '\n');

    n3 = n1 + n2;
    auto arr3 = new int[n3];
    for (int k = 0, i = 0, j = 0; k < n3; ++k) {
        if (arr1[i] <= arr2[j] && i < n1 || j == n2) {
            arr3[k] = arr1[i];
            i++;
        } else {
            arr3[k] = arr2[j];
            j++;
        }
        // cout << "k = " << k << ", i = " << i << ", j = " << j << endl;
    }

    for (int i = 0; i < n3; ++i)
        cout << arr3[i] << (i < n3 - 1 ? ' ' : '\n');

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}