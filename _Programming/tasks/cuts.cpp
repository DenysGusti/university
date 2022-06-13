#include <iostream>

using namespace std;

struct Matrix {
    size_t rows{}, columns{};
    bool **arr{};

    Matrix(size_t m, size_t n) : rows{m}, columns{n} {
        arr = new bool *[rows];
        for (size_t i = 0; i < rows; ++i)
            arr[i] = new bool[columns];
    }

    void read() const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                cin >> arr[i][j];
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

void dfs(const size_t i, const size_t j, Matrix &visited, const Matrix &field) {
    visited.arr[i][j] = true;
    if (i < field.rows - 1)
        if (!visited.arr[i + 1][j] && !field.arr[i + 1][j])
            dfs(i + 1, j, visited, field);
    if (j < field.columns - 1)
        if (!visited.arr[i][j + 1] && !field.arr[i][j + 1])
            dfs(i, j + 1, visited, field);
    if (i > 0)
        if (!visited.arr[i - 1][j] && !field.arr[i - 1][j])
            dfs(i - 1, j, visited, field);
    if (j > 0)
        if (!visited.arr[i][j - 1] && !field.arr[i][j - 1])
            dfs(i, j - 1, visited, field);
}

int solve(const Matrix &field) {
    int parts{};
    Matrix visited(field.rows, field.columns);
    for (size_t i = 0; i < visited.rows; ++i)
        for (size_t j = 0; j < visited.columns; ++j)
            visited.arr[i][j] = false;

    for (size_t i = 0; i < visited.rows; ++i)
        for (size_t j = 0; j < visited.columns; ++j)
            if (!field.arr[i][j] && !visited.arr[i][j]) {
                dfs(i, j, visited, field);
                ++parts;
            }
    return parts;
}

int main() {
    size_t a, b;
    cin >> a >> b;
    Matrix field(a, b);
    field.read();
    field.print();
    cout << solve(field) << endl;
    return 0;
}

/*
3 5
0 1 0 1 0
1 0 0 1 0
0 1 1 0 1

5 8
0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1
0 1 0 1 0 1 0 1
0 0 0 0 0 0 0 0
1 0 1 0 1 0 1 0

3 7
0 0 1 0 0 1 0
0 1 0 0 1 0 1
1 0 1 0 1 0 0
*/
