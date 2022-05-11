// Реалізувати структуру Пряма з дійсними полями A,B,C, які відповідатимуть рівнянню прямої Ax+By+C=0.
// Користувач вводить n прямих. Занести їх у масив, видрукувати прямі, які є паралельними.
// Для перевірки на паралельність прямих організувати метод в структурі.

#include "cp3_2.h"

using namespace std;

int main() {
    size_t n;
    cout << "Введіть кількість прямих: ";
    cin >> n;
    auto arr = new Line *[n]{};

    try {
        for (size_t i = 0; i < n; ++i) {
            ld a, b, c;
            cout << "Введіть A, B, C:\n";
            cin >> a >> b >> c;
            if (!(static_cast<bool>(a) || static_cast<bool>(b)))
                throw (logic_error("A і B не можуть одночасно = 0"));
            arr[i] = new Line(a, b, c);
        }

        cout << "Прямі:\n";
        for (size_t i = 0; i < n; ++i)
            arr[i]->print();

        for (size_t i = 0; i < n; ++i) {
            cout << "\nПаралельні до: ";
            arr[i]->print();
            for (size_t j = 0; j < n; ++j)
                if (i != j && arr[i]->isParallel(*arr[j]))
                    arr[j]->print();
        }

    } catch (const logic_error &e) {
        cerr << e.what();
    }

    for (size_t i = 0; i < n; ++i)
        delete arr[i];
    delete[] arr;
    return 0;
}

/*
6
0 1 0
1 0 -2
-1 1 1
-1 1 -1
0 1 -3
-2 1 3
*/

