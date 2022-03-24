// Користувач вводить послідовність дійсних чисел розміру n.
// Видалити усі числа, які є менші за середнє значення і надрукувати результат.
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    long double average{};
    cout << "n = ";
    cin >> n;
    vector<long double> arr(n);
    cout << "array: ";
    for (auto &i: arr) {
        cin >> i;
        average += i;
    }
    average /= n;
    cout << "average = " << average << '\n';
    for (int i = n - 1; i >= 0; --i)
        if (arr[i] < average)
            arr.erase(arr.begin() + i);
    cout << "new array: ";
    for (const auto &i: arr)
        cout << i << ' ';
    cout << endl;
    return 0;
}
// -1 2 -3 4 -5 6 -7 8 -9 10