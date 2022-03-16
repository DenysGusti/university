// Надрукувати найбільшу цифру двоцифрового числа, яке вводиться користувачем.
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int first_digit = n / 10, second_digit = n % 10;
    cout << (first_digit > second_digit ? first_digit : second_digit) << endl;
    return 0;
}