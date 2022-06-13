#include <iostream>

using namespace std;

struct Matrix {
    size_t rows{}, columns{};
    int **arr{};

    Matrix(size_t m, size_t n) : rows{m}, columns{n} {
        arr = new int *[rows];
        for (size_t i = 0; i < rows; ++i)
            arr[i] = new int[columns];
    }

    void fill() const {
        srand(time(nullptr));
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                arr[i][j] = rand() % 9;
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                cout << arr[i][j] << (j < columns - 1 ? ' ' : '\n');
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i)
            delete arr[i];
        delete[] arr;
    }
};

void quadruple(Matrix &abc, Matrix &m) {
    size_t n = abc.rows;

    for (int t = 0; t < 4; ++t) {
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                m.arr[i + (t == 2 || t == 3 ? n : 0)][j + (t == 1 || t == 2 ? n : 0)] = abc.arr[i][j];

        for (size_t i = 0; i < n; ++i)
            for (size_t j = i + 1; j < n; ++j)
                swap(abc.arr[i][j], abc.arr[j][i]);

        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n - j; ++j)
                swap(abc.arr[i][j], abc.arr[i][n - 1 - j]);
    }
}

int main() {
    size_t s;
    cin >> s;
    Matrix abc(s, s);
    abc.fill();
    abc.print();

    Matrix matrix(s * 2, s * 2);
    quadruple(abc, matrix);
    cout << '\n';
    matrix.print();
    return 0;
}

/*
3
1 2 3
4 5 6
7 8 9
*/
