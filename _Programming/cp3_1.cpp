// Реалізувати структуру Комп’ютер з полями: Виробник (стрічка), Процесор (стрічка), Об’єм оперативної пам’яті
// (ціле число), Ціна (ціле число). Зчитати список комп’ютерів, заданий у вхідному файлі. Посортувати по Ціні,
// вивести у вихідний файл. Вивести на екран інформацію про найдорожчий комп’ютер кожного виробника.

#include "cp3_1.h"

int main() {
    fstream fs{"cp3_1.txt"};

    if (fs.is_open()) {
        try {
            size_t n; // то саме що unsigned
            fs >> n;
            auto arr = new Computer *[n];

            for (size_t i = 0; i < n; ++i) {
                string m, pr;
                int ram, p;
                fs >> m >> pr >> ram >> p;
                arr[i] = new Computer(m, pr, ram, p);
            }

            printArray(cout, "Масив:", arr, n);
            mergeSort(arr, n);
            printArray(cout, "Посортовані по ціні:", arr, n);

            fs.seekg(0, ios::end); // дописую, вказівник на кінець
            printArray(fs, "Посортовані по ціні:", arr, n);

            auto man_arr = new string[n]{};
            auto price_arr = new int[n]{};

            size_t s = createArrays(arr, n, man_arr, price_arr);

            cout << "\nНайдорожчі комп'ютери виробників:\n";
            for (size_t i = 0; i < s; ++i)
                cout << "Виробник: " << man_arr[i] << "\t\tЦіна $: " << price_arr[i] << '\n';

            for (size_t i = 0; i < n; ++i)
                delete arr[i];
            delete[] arr;
            delete[] man_arr;
            delete[] price_arr;
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    } else
        cerr << "Файл не відкрився" << endl;
    return 0;
}

/*
10
Apple Celeron 1 1000
Microsoft CoreI7 16 1200
Google CoreI3  8 500
Mcdonalds Ryzen3 2 2020
LPNU CoreI9 32 9999
LPNU CoreI3 2 231
LPNU Ryzen5 8 2020
Google Duos 1 500
Apple CoreI3 8 1000
Microsoft CoreI3 4 1200

*/
