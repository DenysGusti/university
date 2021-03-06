/* Для заданого n (n > 2) написати функцію (з використанням прототипу), вигляду.
 Стрічки та масиви не використовувати.*/

#include <iostream>

using namespace std;

void print_table(int n);

int main() {
    int n;
    cout << "n = ";
    cin >> n;
    print_table(n);
    return 0;
}

void print_table(const int n) {
    for (int j = 2; j <= 2 * n; j += 2) // йдемо по стовпцях від 2 до 2n з кроком 2
        for (int i = j; i <= 2 * (n - 1) + j; i += 2) // йдемо по рядках від j до 2n + j - 2 з кроком 2
            cout << (i - 1) % (2 * n) + 1 << (i < 2 * (n - 1) + j ? '\t' : '\n'); // якщо кінець циклу, новий рядок
    // всі i в таблиці 2n-періодичні, тому обрізаємо по модулю 2n і робимо зміщення -1 +1, щоб можна було вивести 2n
}