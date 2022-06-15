#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Matrix {
    size_t rows{}, columns{};
    int **arr{};

    Matrix() = default;

    Matrix(size_t m, size_t n) : rows{m}, columns{n} {
        arr = new int *[rows];
        for (size_t i = 0; i < rows; ++i)
            arr[i] = new int[columns]{};
    }

    void read(istream &in) const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                in >> arr[i][j];
    }

    void print(ostream &out) const {
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < columns; ++j)
                out << setw(3) << arr[i][j] << (j < columns - 1 ? ' ' : '\n');
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i)
            delete arr[i];
        delete[] arr;
    }
};

void mergeSort(int *a, size_t n, bool reversed) {
    size_t block_size, block_it, l_it, r_it, l_border, r_border, m_border, i;
    auto sort_block = new int[n];
    for (block_size = 1; block_size < n; block_size *= 2)
        for (block_it = 0; block_it < n - block_size; block_it += 2 * block_size) {
            l_it = 0, r_it = 0;
            l_border = block_it, m_border = block_it + block_size, r_border = min(block_it + 2 * block_size, n);
            while (l_border + l_it < m_border && m_border + r_it < r_border) {
                if (reversed ? a[l_border + l_it] > a[m_border + r_it] : a[l_border + l_it] < a[m_border + r_it]) {
                    sort_block[l_it + r_it] = a[l_border + l_it];
                    l_it++;
                } else {
                    sort_block[l_it + r_it] = a[m_border + r_it];
                    r_it++;
                }
            }
            for (; l_border + l_it < m_border; ++l_it)
                sort_block[l_it + r_it] = a[l_border + l_it];
            for (; m_border + r_it < r_border; ++r_it)
                sort_block[l_it + r_it] = a[m_border + r_it];
            for (i = 0; i < l_it + r_it; ++i)
                a[l_border + i] = sort_block[i];
        }
    delete[] sort_block;
}

int main() {
    ifstream fin{"fnc.txt"};
    ofstream fout{"problem4.txt"};
    const size_t n = 2;
    Matrix *matrices[n];
    int sums[n]{};

    cout << "Input:\n";
    fout << "Input:\n";
    for (size_t a, b, i = 0; i < n; ++i, cout << '\n', fout << '\n') {
        fin >> a >> b;
        matrices[i] = new Matrix(a, b);
        matrices[i]->read(fin);
        cout << matrices[i]->columns << ' ' << matrices[i]->rows << '\n';
        fout << matrices[i]->columns << ' ' << matrices[i]->rows << '\n';
        matrices[i]->print(cout);
        matrices[i]->print(fout);
    }

    for (size_t k = 0; k < n; ++k) {
        auto col = new int[matrices[k]->rows]{};
        for (size_t i = 0; i < matrices[k]->rows; ++i)
            for (size_t j = 0; j < matrices[k]->columns; ++j)
                sums[k] += matrices[k]->arr[i][j];

        for (size_t i = 0; i < matrices[k]->rows; ++i)
            col[i] = matrices[k]->arr[i][0];

        if (sums[k] > 0)
            mergeSort(col, matrices[k]->rows, false);
        else
            mergeSort(col, matrices[k]->rows, true);

        for (size_t i = 0; i < matrices[k]->rows; ++i)
            matrices[k]->arr[i][0] = col[i];
        delete[] col;
    }

    cout << "Output:\n";
    fout << "Output:\n";
    for (size_t i = 0; i < n; ++i, cout << '\n', fout << '\n') {
        cout << "Sum of matrix: " << sums[i] << '\n';
        fout << "Sum of matrix: " << sums[i] << '\n';

        matrices[i]->print(cout);
        matrices[i]->print(fout);
    }

    for (size_t i = 0; i < n; ++i)
        delete matrices[i];
    return 0;
}