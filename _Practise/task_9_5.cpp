/*
 Написати підпрограми (оформити з використанням *.h файлів) для роботи зі стеком на базі двонапрямного списку.
 Повинні бути методи запису в стек, читання зі стека (типу PUSH та POP) та модифікації вказівника стеку
 (типу роботи з SP - stack pointer). Написати іншу функціональність для керування кількома стеками звертаючись при цьому
 до створених раніше підпрограм. Використовуючи створені підпрограми в основній програмі прочитати масив цілих чисел та
 вивести в оберненому порядку спочатку числа на позиціях, що кратні трьом, а потім всі інші.
 Масив переглядати лише один раз.
*/

#include <iostream>
#include <fstream>
#include "task_9_5.h"

int main() {
    DoublyLinkedList<int> arr;
    for (int i = 0; i < 35'000'000; ++i)
        arr.push_back(i);
    cout << "good" << endl;
    auto start = chrono::steady_clock::now();
    auto p = arr.at(17'599'998);
    cout << p;
    auto end = chrono::steady_clock::now();
    chrono::duration<double> time = end - start;
    cout << endl << time.count() << endl;
//    bool input = false; // відповідає за те, чи ввід з клавіатури, чи з файлу
//    Stack<int> stack1, stack2; // власний стек на основі двонапрямного списку
//    fstream fs{"task_9_5.txt"};
//    // якщо ввід з клавіатури, peek дивиться наступний символ, але не переміщується, на відміну від get
//    for (int i = 1, c; input && cin.peek() != '\n' && cin >> c || !input && fs >> c; ++i)
//        (i % 3 ? stack2 : stack1).push(c); // якщо позиція ділиться на 3, пушу в перший стек, інакше в другий
//
//    while (!stack1.empty()) { // виводжу перший стек (last in first out - виводиться задом наперед)
//        cout << stack1.top() << ' ';
//        stack1.pop();
//    }
//
//    while (!stack2.empty()) { // виводжу другий стек
//        cout << stack2.top() << ' ';
//        stack2.pop();
//    }
    return 0;
}