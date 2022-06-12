#include <iostream>
#include <iomanip>

using namespace std;

struct Matrix {
    size_t rows{}, columns{};
    int **arr{};

    Matrix(size_t m, size_t n) : rows{m}, columns{n} {
        arr = new int *[rows];
        for (size_t i = 0; i < rows; ++i)
            arr[i] = new int[columns];
    }

    void read() const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                cin >> arr[i][j];
    }

    void print() const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                cout << setw(2) << arr[i][j] << (j < columns - 1 ? ' ' : '\n');
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i)
            delete arr[i];
        delete[] arr;
    }
};

int kadane(const int *arr, size_t &start, size_t &finish, size_t n) {
    int sum{}, maxSum = INT_MIN;
    size_t local_start{}, i;
    finish = -1;

    for (i = 0; i < n; ++i) {
        sum += arr[i];
        if (sum < 0) {
            sum = 0;
            local_start = i + 1;
        } else if (sum > maxSum) {
            maxSum = sum;
            start = local_start;
            finish = i;
        }
    }

    if (finish != -1)
        return maxSum;

    maxSum = arr[0];
    start = finish = 0;

    for (i = 1; i < n; i++)
        if (arr[i] > maxSum) {
            maxSum = arr[i];
            start = finish = i;
        }
    return maxSum;
}

void findMaxSum(const Matrix &abc) {
    int maxSum = INT_MIN, sum, *temp = new int[abc.rows];
    size_t finalLeft{}, finalRight{}, finalTop{}, finalBottom{}, left, right, t, i, start{}, finish{};

    for (left = 0; left < abc.columns; ++left) {
        for (t = 0; t < abc.rows; ++t)
            temp[t] = 0;

        for (right = left; right < abc.columns; ++right) {
            for (i = 0; i < abc.rows; ++i)
                temp[i] += abc.arr[i][right];

//            cout << "\ntemp[" << right << "]: ";
//            for (i = 0; i < abc.rows; ++i)
//                cout << temp[i] << ' ';
//            cout << '\n';

            sum = kadane(temp, start, finish, abc.rows);
            if (sum > maxSum) {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
//            cout << "sum: " << sum << "\tl: " << finalLeft << "\tr: " << finalRight <<
//                 "\tt: " << finalTop << "\tb: " << finalBottom << '\n';
        }
    }

    cout << "(" << finalTop << ", " << finalLeft << ") - (" << finalBottom << ", " << finalRight << ")\t\t(" <<
         finalBottom - finalTop << ", " << finalRight - finalLeft << ")\t\t sum = " << maxSum << endl;
    delete[] temp;
}

int main() {
    size_t m, n;
    cin >> m >> n;
    Matrix abc(m, n);
    abc.read();
    abc.print();
    findMaxSum(abc);
    return 0;
}
/*
4 4
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2

4 5
1 2 -1 -4 -20
-8 -3 4 2 1
3 8 10 1 3
-4 -1 1 7 -6
*/
