#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\bilet_1\problemin.txt)"};
    const int tests = 2;
    char arr[tests][100];

    cout << "Input:\n";
    for (size_t i = 0; i < tests; ++i) {
        fin.getline(arr[i], 100);
        cout << arr[i] << "\n\n";
    }

    cout << "Output:\n";
    for (size_t i = 0; i < tests; ++i) {
        char *res = arr[i], buf[100], rev[100];

        for (size_t len; res; res = strchr(res, ' '), res ? ++res : nullptr) {
            len = strchr(res, ' ') ? strchr(res, ' ') - res : strchr(res, '.') - res;
            strncpy_s(buf, res, len);

            strcpy_s(rev, buf);
            for (size_t j = 0; j < len - j; ++j)
                swap(rev[j], rev[len - 1 - j]);

            if (strstr(res + 1, rev))
                if (strstr(res + 1, rev)[-1] == ' ' &&
                    (strstr(res + 1, rev)[len] == ' ' || strstr(res + 1, rev)[len] == '.'))
                    cout << buf << " - " << rev << '\n';
        }

        cout << '\n';
    }
    return 0;
}