// Реалізувати структуру Комп’ютер з полями: Виробник (стрічка), Процесор (стрічка), Об’єм оперативної пам’яті
// (ціле число), Ціна (ціле число). Зчитати список комп’ютерів, заданий у вхідному файлі. Посортувати по Ціні,
// вивести у вихідний файл. Вивести на екран інформацію про найдорожчий комп’ютер кожного виробника.

#include <iostream>
#include <fstream>

using namespace std;

struct Computer {
    string Manufacturer{};
    string Processor{};
    int RAM{};
    int Price{};

    Computer(string_view m, string_view pr, int ram, int p) : Manufacturer{m}, Processor{pr}, RAM{ram}, Price{p} {}
};

void mergeSort(Computer **a, size_t n) {
    size_t block_size, block_it, l_it, r_it, l_border, r_border, m_border, i;
    auto sort_block = new Computer *[n];
    for (block_size = 1; block_size < n; block_size *= 2)
        for (block_it = 0; block_it < n - block_size; block_it += 2 * block_size) {
            l_it = 0, r_it = 0;
            l_border = block_it, m_border = block_it + block_size, r_border = min(block_it + 2 * block_size, n);
            while (l_border + l_it < m_border && m_border + r_it < r_border) {
                if (a[l_border + l_it]->Price < a[m_border + r_it]->Price) {
                    sort_block[l_it + r_it] = a[l_border + l_it];
                    l_it++;
                } else {
                    sort_block[l_it + r_it] = a[m_border + r_it];
                    r_it++;
                }
            }
            for (; l_border + l_it < m_border; ++l_it)
                sort_block[l_it + r_it] = a[l_border + l_it];
            for (; m_border + r_it < r_border; ++r_it)
                sort_block[l_it + r_it] = a[m_border + r_it];
            for (i = 0; i < l_it + r_it; ++i)
                a[l_border + i] = sort_block[i];
        }
    delete[] sort_block; // звільняю тільки пойнтер на масив пойнтерів, не самі пойнтери, бо видаляться об'єкти
}

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

            cout << "Масив:\n";
            for (size_t i = 0; i < n; ++i)
                cout << arr[i]->Manufacturer << ' ' << arr[i]->Processor << ' ' << arr[i]->RAM << ' ' << arr[i]->Price
                     << '\n';

            mergeSort(arr, n);

            cout << "\nПосортовані по ціні:\n";
            for (size_t i = 0; i < n; ++i)
                cout << arr[i]->Manufacturer << ' ' << arr[i]->Processor << ' ' << arr[i]->RAM << ' ' << arr[i]->Price
                     << '\n';

            fs.seekg(0, ios::end); // дописую, вказівник на кінець
            fs << "\n";
            for (size_t i = 0; i < n; ++i)
                fs << arr[i]->Manufacturer << ' ' << arr[i]->Processor << ' ' << arr[i]->RAM << ' ' << arr[i]->Price
                   << '\n';

            auto man_arr = new string[n]{};
            auto price_arr = new int[n]{};

            size_t s{};
            for (size_t i = 0; i < n; ++i) {
                bool found = false;
                for (size_t j = 0; j < s; ++j)
                    if (man_arr[j] == arr[i]->Manufacturer) {
                        price_arr[j] = max(price_arr[j], arr[i]->Price);
                        found = true;
                        break;
                    }
                if (!found) {
                    man_arr[s] = arr[i]->Manufacturer;
                    price_arr[s] = arr[i]->Price;
                    ++s;
                }
            }

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
