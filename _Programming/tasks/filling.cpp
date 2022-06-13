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

    void fillDiagonally(const int s, const int t, const int mode) const {
        if (rows == columns)
            for (size_t n = rows, tr = 1, a, b, i = 0; i < n * n - i; ++i) {
                a = tr - tr * (tr + 1) / 2 + i;
                b = mode == 1 ? n - tr + a : tr - 1 - a;
                arr[a][b] = s + t * i;
                arr[n - 1 - a][n - 1 - b] = s + t * (n * n - 1 - i);

                if (i == tr * (tr + 1) / 2 - 1)
                    ++tr;
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
    int s, t;
    size_t p;
    cin >> p;
    cout << "s, t = ";
    cin >> s >> t;

    Matrix abc(p, p);
    abc.fillDiagonally(s, t, 1);
    abc.print();
    cout << '\n';
    abc.fillDiagonally(s, t, -1);
    abc.print();
    return 0;
}