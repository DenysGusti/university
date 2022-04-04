#include <iostream>

void enter_c_matrix(int **arr, const int m, const int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> arr[i][j];
}

void print_c_matrix(int **arr, const int m, const int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            std::cout << arr[i][j] << (j < n - 1 ? ' ' : '\n');
}

void swap_columns(int **arr, const int m, const int a, const int b) {
//    int c;
    for (int i = 0; i < m; ++i) {
        std::swap(arr[i][a], arr[i][b]);
//        c = arr[i][a];
//        arr[i][a] = arr[i][b];
//        arr[i][b] = c;
    }
}

int main() {
    int m, n, a, b;
    std::cout << "enter m, n: ";
    std::cin >> m >> n;
    int **arr = new int *[m];
    for (int i = 0; i < m; ++i)
        arr[i] = new int[n];
    enter_c_matrix(arr, m, n);
    print_c_matrix(arr, m, n);
    std::cout << "enter columns a, b you want to swap: ";
    std::cin >> a >> b;
    swap_columns(arr, m, a - 1, b - 1);
    print_c_matrix(arr, m, n);
    for (int i = 0; i < m; ++i)
        delete arr[i];
    delete[] arr;
    return 0;
}