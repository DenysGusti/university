#include <fstream>
#include "task_9_5.h"

/*
 Написати підпрограми (оформити з використанням *.h файлів) для роботи зі стеком на базі двонапрямного списку.
 Повинні бути методи запису в стек, читання зі стека (типу PUSH та POP) та модифікації вказівника стеку
 (типу роботи з SP - stack pointer). Написати іншу функціональність для керування кількома стеками звертаючись при цьому
 до створених раніше підпрограм. Використовуючи створені підпрограми в основній програмі прочитати масив цілих чисел та
 вивести в оберненому порядку спочатку числа на позиціях, що кратні трьом, а потім всі інші.
 Масив переглядати лише один раз.
*/

int main() {
    bool input = false;
    Stack<int> stack1, stack2;
    fstream fs{"task_9_5.txt"};

    for (int i = 1, c; input && cin.peek() != '\n' && cin >> c || !input && fs >> c; ++i)
        (i % 3 ? stack2 : stack1).push(c);

    while (!stack1.empty()) {
        cout << stack1.top() << ' ';
        stack1.pop();
    }

    while (!stack2.empty()) {
        cout << stack2.top() << ' ';
        stack2.pop();
    }
    return 0;
}

/*    DoublyLinkedList<int> uuu;
    cout << uuu.front() << endl;
    DoublyLinkedList<int> obj = {1, 2, 3};
    cout << obj.empty() << endl;
    obj.push_front(3);
    obj.push_back(2);
    obj.push_front(1);
    obj.push_back(4);
    cout << obj.size() << endl;
    DoublyLinkedList new_obj{obj};
    new_obj.print();
    obj.pop_back();
    new_obj.pop_front();
    obj.print();
    new_obj.print();
    cout << new_obj.back() << endl;
    cout << obj.size() << ' ' << new_obj.size();
    Stack<int> s{};
    s.push(2);
    cout << s.top() << endl;*/