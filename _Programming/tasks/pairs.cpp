#include <iostream>

using namespace std;

void mergeSort(int *arr, size_t m) {
    size_t n = m / 2, block_size, block_it, l_it, r_it, l_border, r_border, m_border, i;
    auto a = new int[n], b = new int[n];

    for (size_t k = 0; k < n; ++k) {
        a[k] = arr[2 * k];
        b[k] = arr[2 * k + 1];
    }

    auto sort_block_a = new int[n], sort_block_b = new int[n];
    for (block_size = 1; block_size < n; block_size *= 2)
        for (block_it = 0; block_it < n - block_size; block_it += 2 * block_size) {
            l_it = 0, r_it = 0;
            l_border = block_it, m_border = block_it + block_size, r_border = min(block_it + 2 * block_size, n);
            while (l_border + l_it < m_border && m_border + r_it < r_border)
                if (a[l_border + l_it] < a[m_border + r_it]) {
                    sort_block_a[l_it + r_it] = a[l_border + l_it];
                    sort_block_b[l_it + r_it] = b[l_border + l_it];
                    l_it++;
                } else {
                    sort_block_a[l_it + r_it] = a[m_border + r_it];
                    sort_block_b[l_it + r_it] = b[m_border + r_it];
                    r_it++;
                }
            for (; l_border + l_it < m_border; ++l_it) {
                sort_block_a[l_it + r_it] = a[l_border + l_it];
                sort_block_b[l_it + r_it] = b[l_border + l_it];
            }
            for (; m_border + r_it < r_border; ++r_it) {
                sort_block_a[l_it + r_it] = a[m_border + r_it];
                sort_block_b[l_it + r_it] = b[m_border + r_it];
            }
            for (i = 0; i < l_it + r_it; ++i) {
                a[l_border + i] = sort_block_a[i];
                b[l_border + i] = sort_block_b[i];
            }
        }

    for (size_t k = 0; k < m; ++k)
        arr[k] = (k % 2 ? b[k / 2] : a[k / 2]);

    delete[] a;
    delete[] b;
    delete[] sort_block_a;
    delete[] sort_block_b;
}

int main() {
    size_t n;
    cin >> n;
    auto arr = new int[2 * n]{};
    srand(time(nullptr));
    for (size_t i = 0; i < 2 * n; ++i)
        arr[i] = rand() % 1000 - 500;

    for (size_t i = 0; i < 2 * n; ++i)
        cout << arr[i] << (i < 2 * n - 1 ? ' ' : '\n');

    mergeSort(arr, 2 * n);
    for (size_t i = 0; i < 2 * n; ++i)
        cout << arr[i] << (i < 2 * n - 1 ? ' ' : '\n');
    return 0;
}