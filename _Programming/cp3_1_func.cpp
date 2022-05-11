#include "cp3_1.h"

using namespace std;

Computer::Computer(string_view m, string_view pr, int ram, int p)
        : Manufacturer{m}, Processor{pr}, RAM{ram}, Price{p} {}

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

void printArray(ostream &out, string_view message, Computer **arr, size_t n) {
    out << '\n' << message << '\n';
    for (size_t i = 0; i < n; ++i)
        out << arr[i]->Manufacturer << ' ' << arr[i]->Processor << ' ' << arr[i]->RAM << ' ' << arr[i]->Price
            << '\n';
}

size_t createArrays(Computer **arr, size_t n, string *man_arr, int *price_arr) {
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
    return s;
}