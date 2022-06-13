#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Matrix {
    size_t rows{}, columns{};
    int **arr{};

    Matrix(size_t m, size_t n) : rows{m}, columns{n} {
        arr = new int *[rows];
        for (size_t i = 0; i < rows; ++i)
            arr[i] = new int[columns]{};
    }

    void fillDiagonally() const {
        if (rows == columns)
            for (size_t n = rows, tr = 1, in = 1, i = 0; i < n * n - i; ++i) {
                arr[in - tr + i][n - tr + i] = i + 1;
                arr[n - in + tr - 1 - i][tr - 1 - i] = n * n - i;

                if (i == tr - 1)
                    tr += ++in;
            }
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                cout << setw(ceil(log10(rows * rows + 1))) << arr[i][j] << (j < columns - 1 ? ' ' : '\n');
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i)
            delete arr[i];
        delete[] arr;
    }
};

int main() {
    size_t p;
    cin >> p;
    Matrix abc(p, p);
    abc.fillDiagonally();
    abc.print();
    return 0;
}