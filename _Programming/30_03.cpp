#include <iostream>

void print_matrix(int **arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            std::cout << arr[i][j] << ' ';
        std::cout << '\n';
    }
}

int *max_in_columns(int **arr, int n, int m) {
    int *c = new int[m];
    for (int j = 0; j < m; ++j) {
        int max_c = arr[0][j];
        for (int i = 0; i < n; ++i) {
            if (arr[i][j] > max_c) {
                max_c = arr[i][j];
            }
        }
        c[j] = max_c;
    }
    return c;
}

int upper_sum(int **arr, int n, int m) {
    int s = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < m; ++j)
            s += arr[i][j];
    return s;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int **arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
        for (int j = 0; j < m; ++j)
            std::cin >> arr[i][j];
    }
    print_matrix(arr, n, m);
    std::cout << upper_sum(arr, n, m) << std::endl;
    max_in_columns(arr, n, m);
    int *d = max_in_columns(arr, n, m);
    for (int i = 0; i < m; ++i)
        std::cout << d[i] << ' ';
    return 0;
}