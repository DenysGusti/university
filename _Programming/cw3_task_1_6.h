#ifndef UNIVERSITY_CW3_TASK_1_6_H
#define UNIVERSITY_CW3_TASK_1_6_H

#include <iostream>
#include <cstring>

using namespace std;

struct Car {
    char *brand{}, *model{};
    int year{};
    double volume{};

    Car(char *b, char *m, int y, double v);
};

void mergeSort(Car **a, size_t n, int method);

void printArray(ostream &out, const char *message, Car **arr, size_t n);

Car::Car(char *b, char *m, const int y, const double v) : brand{_strdup(b)}, model{_strdup(m)}, year{y}, volume{v} {}

void mergeSort(Car **a, size_t n, int method) {
    size_t block_size, block_it, l_it, r_it, l_border, r_border, m_border, i;
    auto sort_block = new Car *[n];
    for (block_size = 1; block_size < n; block_size *= 2)
        for (block_it = 0; block_it < n - block_size; block_it += 2 * block_size) {
            l_it = 0, r_it = 0;
            l_border = block_it, m_border = block_it + block_size, r_border = min(block_it + 2 * block_size, n);
            while (l_border + l_it < m_border && m_border + r_it < r_border) {
                if (method == 0 ? strcmp(a[l_border + l_it]->brand, a[m_border + r_it]->brand) < 0 :
                    strcmp(a[l_border + l_it]->model, a[m_border + r_it]->model) < 0) {
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
    delete[] sort_block;
}

void printArray(ostream &out, const char *message, Car **arr, size_t n) {
    out << '\n' << message << '\n';
    for (size_t i = 0; i < n; ++i)
        out << arr[i]->brand << ' ' << arr[i]->model << ' ' << arr[i]->year << ' ' << arr[i]->volume << '\n';
}

void findTheOldest(Car **a, size_t n) {
    int y = a[0]->year;
    for (size_t i = 0; i < n; ++i)
        y = min(y, a[i]->year);

    cout << "\nНайстаріші автомобілі:\n";
    for (size_t i = 0; i < n; ++i)
        if (a[i]->year == y)
            cout << a[i]->brand << ' ' << a[i]->model << ' ' << a[i]->year << ' ' << a[i]->volume << '\n';
}

#endif
