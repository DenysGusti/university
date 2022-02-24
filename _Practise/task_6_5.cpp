/* Задано натуральне число n. Знайти різницю між двома числами, перше з яких побудоване на основі непарних цифр n зліва
 * направо числа, а друге - на основі парних. Якщо 0 буде в найстаршому розряді - пропускати його. Стрічки та масиви не
 * використовувати. Приклади: n = 2352361 -> 3531 - 226, n = 70892014 -> 791 - 8204. */
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    unsigned long long int n;
    cout << "n = ";
    cin >> n;
    cout << '\n' << "n = " << n << endl;

    unsigned long long int num1 = 0, num2 = 0;
    short int i = 0, j = 0;
    while (n) {
        unsigned short int last_digit = n % 10;
        if (last_digit & 1) {
            num1 += last_digit * (unsigned long long int) pow(10, i);
            i++;
        } else {
            num2 += last_digit * (unsigned long long int) pow(10, j);
            j++;
        }
        n /= 10;
    }

    long long int res = num1 - num2;
    cout << num1 << " - " << num2 << " = " << res << endl;
    return 0;
}