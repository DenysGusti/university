#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    ifstream fin{"problemin.txt"};
    const size_t tests = 2;
    char arr[tests][100], ans[tests][100];

    for (size_t i = 0; i < tests; ++i, fin.ignore(100, '\n')) {
        fin.get(arr[i], 100, '.');
        fin.ignore(100, '\n');

        arr[i][strlen(arr[i]) + 1] = '\0';
        arr[i][strlen(arr[i])] = '.';
    }

    for (size_t i = 0; i < tests; ++i) {
        bool flag{};
        size_t k = -1;
        for (size_t j = 0; j < strlen(arr[i]); ++j) {
            if (!flag) {
                if (arr[i][j] == ' ') {
                    flag = true;
                    ans[i][++k] = arr[i][j];
                } else
                    ans[i][++k] = arr[i][j];
            } else if (arr[i][j] != ' ') {
                flag = false;
                ans[i][++k] = arr[i][j];
            }
        }

        ans[i][k - 1] = '.';
        ans[i][k] = '\0';
    }

    cout << "Input:\n";
    for (size_t i = 0; i < tests; ++i)
        cout << arr[i] << "\n\n";
    cout << "Output:\n";
    for (size_t i = 0; i < tests; ++i)
        cout << ans[i] << "\n\n";
    return 0;
}