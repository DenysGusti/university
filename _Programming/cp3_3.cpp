//Користувач вводить 2 списки (розмірів n та m) слів.
// Вивести всі слова, які присутні в обох масивах. Використовувати стрічки в стилі С.

#include <iostream>
#include <cstring>

using namespace std;

int main() {
    size_t m, n;
    cout << "Введіть m та n: ";
    cin >> m >> n;
    char arr1[10][100], arr2[10][100];

    cout << "Введіть 1 масив:\n";
    for (size_t i = 0; i < m; ++i)
        cin >> arr1[i];
    cout << "Введіть 2 масив:\n";
    for (size_t i = 0; i < n; ++i)
        cin >> arr2[i];

    cout << "\n1 масив:\n";
    for (size_t i = 0; i < m; ++i)
        cout << arr1[i] << ' ';
    cout << "\n2 масив:\n";
    for (size_t i = 0; i < n; ++i)
        cout << arr2[i] << ' ';

    cout << "\nСпільні:\n";
    for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < n; ++j)
            if (!strcmp(arr1[i], arr2[j]))
                cout << arr1[i] << ' ';
    return 0;
}

/*
4 4
abc bca ppc abn
pnc abc cmp bca
*/
