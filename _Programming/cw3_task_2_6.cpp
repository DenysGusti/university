// У файлі in1.txt задані імена студентів, які відвідують курс з програмування, у файлі in2.txt задані імена студентів,
// які відвідують курс з історії, а у файлі in3.txt задані імена студентів, які відвідують курс з алгебри. Надрукувати
// імена студентів, які відвідують тільки один курс, у файл out.txt. Дані у файлах задані у довільному форматі й не
// посортовані.

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main() {
    fstream in1("in1.txt"), in2("in2.txt"), in3("in3.txt"), out("out.txt");
    if (in1.is_open() && in2.is_open() && in3.is_open()) {
        char arr1[10][20], arr2[10][20], arr3[10][20], res1[30][20], res2[30][20];

        size_t n1, n2, n3, n4{}, n5{};
        in1 >> n1;
        in2 >> n2;
        in3 >> n3;
        for (size_t i = 0; i < n1; ++i)
            in1 >> arr1[i];
        for (size_t i = 0; i < n2; ++i)
            in2 >> arr2[i];
        for (size_t i = 0; i < n3; ++i)
            in3 >> arr3[i];

        cout << "Курс з програмування: ";
        for (size_t i = 0; i < n1; ++i)
            cout << arr1[i] << ' ';
        cout << "\nКурс з історії: ";
        for (size_t i = 0; i < n3; ++i)
            cout << arr2[i] << ' ';
        cout << "\nКурс з алгебри: ";
        for (size_t i = 0; i < n3; ++i)
            cout << arr3[i] << ' ';

        for (size_t i = 0; i < n1; ++i) {
            bool found = false;
            for (size_t j = 0; j < n4; ++j)
                if (!strcmp(res1[j], arr1[i])) {
                    found = true;
                    break;
                }
            if (!found) {
                strcpy_s(res1[n4], arr1[i]);
                ++n4;
            }
        }
        for (size_t i = 0; i < n2; ++i) {
            bool found = false;
            for (size_t j = 0; j < n4; ++j)
                if (!strcmp(res1[j], arr2[i])) {
                    found = true;
                    break;
                }
            if (!found) {
                strcpy_s(res1[n4], arr2[i]);
                ++n4;
            }
        }
        for (size_t i = 0; i < n3; ++i) {
            bool found = false;
            for (size_t j = 0; j < n4; ++j)
                if (!strcmp(res1[j], arr3[i])) {
                    found = true;
                    break;
                }
            if (!found) {
                strcpy_s(res1[n4], arr3[i]);
                ++n4;
            }
        }

        cout << "\nВсі студенти: ";
        for (size_t i = 0; i < n4; ++i)
            cout << res1[i] << ' ';

        for (size_t counter, j = 0; j < n4; ++j) {
            counter = 0;
            for (size_t i = 0; i < n1; ++i)
                if (!strcmp(res1[j], arr1[i]))
                    ++counter;
            for (size_t i = 0; i < n2; ++i)
                if (!strcmp(res1[j], arr2[i]))
                    ++counter;
            for (size_t i = 0; i < n3; ++i)
                if (!strcmp(res1[j], arr3[i]))
                    ++counter;
            if (counter == 1) {
                strcpy_s(res2[n5], res1[j]);
                ++n5;
            }
        }

        cout << "\nЯкі відвідують тільки 1 курс: ";
        for (size_t i = 0; i < n5; ++i) {
            out << res2[i] << ' ';
            cout << res2[i] << ' ';
        }
    }
    return 0;
}