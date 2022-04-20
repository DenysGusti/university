#include <iostream>
#include <cstring>

using namespace std;

bool check_if_unique(const char str[]) {
    for (int i = 0; i < strlen(str); ++i) {
        char cs = str[i];
        for (int j = i + 1; j < strlen(str); ++j)
            if (cs == str[j])
                return false;
    }
    return true;

}

// В даній стрічці знайти підстрічку найдовшої довжини, в яку символи входитимуть без повторів.
// Наприклад, abcdefa -> abcdef або bcdefa (обидві відповіді будуть зараховані). aaaa -> a

int main() {
    char s[100], ps[100], ns[100];
    cin.getline(s, 100);
    int b = 0, e = 0;

    for (int i = 0; i < strlen(s) - 1; ++i) {
        for (int j = i + 1; j < strlen(s); ++j) {
            strncpy(ps, s + i, j - i + 1);
            ps[j - i + 1] = '\0';
//            cout << i << ' ' << j << endl;
//            cout << j - i + 1 << endl;
//            cout << "not is " << ps << endl;
            if (check_if_unique(ps))
//                cout << "is " << ps << endl;
            if (check_if_unique(ps) && e - b < j - i)
                b = i, e = j;
        }
    }

    strncpy(ns, s + b, e - b + 1);
    cout << ns << endl;
    return 0;
}

// absimvm skivsv scvsvsivkfe
// aaaaaaaaapsdfgdsaaaaaaa
// a
// ab
// abcdefa
// aaaa
// bba