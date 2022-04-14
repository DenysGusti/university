#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream ifs{"text.txt"};
    int n;
    ifs >> n;
    cout << n << '\n';
    int *arr = new int[n];
    for (int i = 0; i < n; ++i)
        ifs >> arr[i];
    for (int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
    for (int i = 0; i < (n - (n & 1)) / 2; ++i) {
        int c = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = c;
    }
    for (int i = 0; i < n; ++i)
        cout << arr[i] << ' ';
    cout << '\n';
    ofstream ofs{"text_new.txt"};
    for (int i = 0; i < n; ++i)
        ofs << arr[i] << ' ';
    return 0;
}