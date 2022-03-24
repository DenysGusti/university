// Користувач вводить послідовність дійсних чисел розміру n.
// Чи можна отримати посортовану послідовність, видаливши тільки один елемент?
// Якщо так - надрукуйте результат, якщо ні, то -1.
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool try_if_sorted(vector<long double> arr, const int &pos) {
    arr.erase(arr.begin() + pos);
    vector<long double> s1_arr(arr), s2_arr(arr);
    sort(s1_arr.begin(), s1_arr.end());
    sort(s2_arr.begin(), s2_arr.end(), greater<>());
//    for (const auto &i: arr)
//        cout << i << (&i == &arr.back() ? '\n' : ' ');
//    for (const auto &i: s1_arr)
//        cout << i << (&i == &s1_arr.back() ? '\n' : ' ');
//    for (const auto &i: s2_arr)
//        cout << i << (&i == &s2_arr.back() ? '\n' : ' ');
    return arr == s1_arr || arr == s2_arr;
}

int main() {
    int n;
    cout << "n = ";
    cin >> n;
    vector<long double> arr(n);
    cout << "array: ";
    for (auto &i: arr)
        cin >> i;
    int i{};
    bool flag = false;
    for (; i < n; ++i)
        if (try_if_sorted(arr, i)) {
            flag = true;
            break;
        }
    if (flag) {
        arr.erase(arr.begin() + i);
        cout << "new array: ";
        for (const auto &j: arr)
            cout << j << ' ';
        cout << "\nвидалений " << i + 1 << "-ий елемент" << endl;
    } else
        cout << -1 << endl;
    return 0;
}
// 1 3 2 4 5