#ifndef UNIVERSITY_CP3_1_H
#define UNIVERSITY_CP3_1_H

#include <iostream>
#include <fstream>

using namespace std;

struct Computer {
    string Manufacturer{}, Processor{};
    int RAM{}, Price{};

    Computer(string_view m, string_view pr, int ram, int p);
};

void mergeSort(Computer **a, size_t n);

void printArray(ostream &out, string_view message, Computer **arr, size_t n);

size_t createArrays(Computer **arr, size_t n, string *man_arr, int *price_arr);

#endif //UNIVERSITY_CP3_1_H
