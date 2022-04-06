// Користувач вводить дві прямокутні матриці дійсних чисел. Перевірити, чи добуток даних матриць є симетричною матрицею.

#include <iostream>

using namespace std;

void enter_c_matrix(double **arr, const int m, const int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> arr[i][j];
}

void print_c_matrix(double **arr, const int m, const int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cout << arr[i][j] << (j < n - 1 ? ' ' : '\n');
}

void multiplicate_matrices(double **a1, const int r1, double **a2, const int r2, const int c2, double **res) {
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j)
            res[i][j] = 0;
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j)
            for (int k = 0; k < r2; ++k)
                res[i][j] += a1[i][k] * a2[k][j];
}

bool check_if_symmetric(double **arr, const int n) {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (arr[i][j] != arr[j][i])
                return false;
    return true;
}

int main() {
    int m1, n1, m2, n2;

    cout << "\nenter size of first martix, m1, n1: ";
    cin >> m1 >> n1;
    auto arr1 = new double *[m1];
    for (int i = 0; i < m1; ++i)
        arr1[i] = new double[n1];
    cout << "\nenter first martix:\n";
    enter_c_matrix(arr1, m1, n1);
    print_c_matrix(arr1, m1, n1);

    cout << "\nenter size of second martix, m2, n2: ";
    cin >> m2 >> n2;
    auto arr2 = new double *[m2];
    for (int i = 0; i < m2; ++i)
        arr2[i] = new double[n2];
    cout << "\nenter second martix:\n";
    enter_c_matrix(arr2, m2, n2);
    print_c_matrix(arr2, m2, n2);

    if (n1 != m2)
        cout << "Multiplication is impossible!" << endl;
    else {
        auto res = new double *[m1];
        for (int i = 0; i < m1; ++i)
            res[i] = new double[n2];
        multiplicate_matrices(arr1, m1, arr2, m2, n2, res);
        cout << "\nmultiplication:\n";
        print_c_matrix(res, m1, n2);
        if (m1 != n2)
            cout << "Symmetric is impossible!" << endl;
        else
            cout << "Матриця " << (check_if_symmetric(res, m1) ? "" : "не" )<< " симетрична" << endl;
    }
    return 0;
}