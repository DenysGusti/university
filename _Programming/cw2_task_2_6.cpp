#include <iostream>
#include <iomanip>

using namespace std;

void enter_c_matrix(double **arr, const int m, const int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];
}

void print_c_matrix(double **arr, const int m, const int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cout << setw(2) << arr[i][j] << (j < n - 1 ? ' ' : '\n');
}

void rotate90(double **m, const int n) {
    // with copy
//    for (int i = 0; i < n; ++i)
//        for (int j = 0; j < n; ++j)
//            arr[i][j] = m[n - 1 - j][i];
    // with swap
    for (int i = 0; i < n; ++i) // transpose
        for (int j = i + 1; j < n; ++j)
            swap(m[i][j], m[j][i]);
    for (int i = 0; i < n; ++i) // reverse
        for (int j = 0; j < (n - (n & 1)) / 2; ++j)
            swap(m[i][j], m[i][n - 1 - j]);
}

//  Користувач вводить дійснозначну матрицю розміром nxn.
//  Повернути її на 90 градусів за годинниковою стрілкою, не створюючи нову матрицю.

int main() {
    int n;

    cout << "Enter size of matrix[n*n]: ";
    cin >> n;

    auto arr = new double *[n];
    for (int i = 0; i < n; ++i)
        arr[i] = new double[n];

    cout << "Enter matrix[n*n]:\n";
    enter_c_matrix(arr, n, n);
    print_c_matrix(arr, n, n);
    cout << '\n';

    rotate90(arr, n);
    print_c_matrix(arr, n, n);

    for (int i = 0; i < n; ++i)
        delete arr[i];
    delete[] arr;

    return 0;
}
// 1 2 3 4 5 6 7 8 9
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16