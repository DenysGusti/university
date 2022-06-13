#include <iostream>

using namespace std;

struct Matrix {
    size_t rows{}, columns{};
    bool **arr{};

    Matrix(size_t m, size_t n) : rows{m}, columns{n} {
        arr = new bool *[rows];
        for (size_t i = 0; i < rows; ++i)
            arr[i] = new bool[columns]{};
    }

    void read() const {
        char tmp;
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j) {
                cin >> tmp;
                arr[i][j] = tmp - '0';
            }
        cout << '\n';
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                cout <<  arr[i][j] << (j < columns - 1 ? "" : "\n");
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i)
            delete arr[i];
        delete[] arr;
    }
};

int findCorners(const Matrix &abc) {
    int counter{};

    for (size_t i = 0; i < abc.rows; ++i)
        for (size_t j = 0; j < abc.columns; ++j) {
            if (i > 0 && j > 0)
                if (abc.arr[i][j] && abc.arr[i - 1][j] && abc.arr[i][j - 1])
                    ++counter;
            if (i < abc.rows - 1 && j < abc.columns - 1)
                if (abc.arr[i][j] && abc.arr[i + 1][j] && abc.arr[i][j + 1])
                    ++counter;
            if (i > 0 && j < abc.columns - 1)
                if (abc.arr[i][j] && abc.arr[i - 1][j] && abc.arr[i][j + 1])
                    ++counter;
            if (i < abc.rows - 1 && j > 0)
                if (abc.arr[i][j] && abc.arr[i + 1][j] && abc.arr[i][j - 1])
                    ++counter;
        }

    return counter;
}

int main() {
    size_t r, c;
    cin >> r >> c;
    Matrix abc(r, c);
    abc.read();
    abc.print();
    cout << findCorners(abc) << endl;
    return 0;
}

/*
7 16
0001011111000111
1101010000000001
1001010100000000
1001000110111000
0001000000001000
0111000000101000
0000000001101000
*/
