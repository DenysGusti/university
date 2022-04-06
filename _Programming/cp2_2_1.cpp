// Користувач вводить n дійсних чисел. Перевірити, яка сума є більшою, лівої половину масиву чи правої.

#include <iostream>

using namespace std;

int main() {
    int n;
    double lsum = 0, rsum = 0;
    cin >> n;
    auto arr = new double[n];
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    for (int i = 0; i < (n - (n & 1)) / 2; ++i) {
        lsum += arr[i];
        rsum += arr[n - 1 - i];
    }

    for (int i = 0; i < n; ++i)
        cout << arr[i] << (i < n - 1 ? ' ' : '\n');
    cout << "Сума лівої половини масиву: " << lsum << "\t Сума правої половини масиву: " << rsum << '\n';
    if (lsum == rsum)
        cout << "Суми рівні" << endl;
    else
        cout << (lsum > rsum ? "Ліва" : "Права") << " сума більша" << endl;
    delete[] arr;
    return 0;
}