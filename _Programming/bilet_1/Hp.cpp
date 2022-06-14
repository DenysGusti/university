#include <iostream>
#include <fstream>

using namespace std;

struct Vector {
    size_t size{};
    int *arr{};

    Vector() = default;

    explicit Vector(size_t s) : size{s} {
        arr = new int[s]{};
    }

    void read(istream &in) const {
        for (size_t i = 0; i < size; ++i)
            in >> arr[i];
    }

    void print(ostream &out) const {
        for (size_t i = 0; i < size; ++i)
            out << arr[i] << (i < size - 1 ? ' ' : '\n');
    }

    int scalarProduct(const Vector &other) const {
        int p{};
        for (size_t i = 0; i < size; ++i)
            p += arr[i] * other.arr[i];
        return p;
    }

    ~Vector() {
        delete[] arr;
    }
};

int main() {
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\bilet_1\fnc.txt)"};
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_Programming\bilet_1\problem4.txt)"};
    const size_t m = 3;
    Vector *vectors[m];

    size_t n;
    fin >> n;

    cout << "Input:\n" << n << '\n';
    fout << "Input:\n" << n << '\n';
    for (size_t i = 0; i < m; ++i) {
        vectors[i] = new Vector(n);
        vectors[i]->read(fin);
        vectors[i]->print(cout);
        vectors[i]->print(fout);
    }

    int u = vectors[0]->scalarProduct(*vectors[1]) + vectors[0]->scalarProduct(*vectors[2]) -
            vectors[1]->scalarProduct(*vectors[2]);

    cout << "Output\n" << u;
    fout << "Output\n" << u;

    for (size_t i = 0; i < m; ++i)
        delete vectors[i];
    return 0;
}