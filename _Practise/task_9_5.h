#ifndef UNTITLED_TASK_9_5_H
#define UNTITLED_TASK_9_5_H

#include <iostream>

using namespace std;

template<class T>
struct DoublyLinkedNode { // нод - одиниця двонапрямного списку
    T data{};
    DoublyLinkedNode *next{}, *prev{}; // пойнтер на наступний і попередній ноди

    DoublyLinkedNode(const T &d, DoublyLinkedNode<T> *n, DoublyLinkedNode<T> *p) : data{d}, next{n}, prev{p} {}

    ~DoublyLinkedNode() { // видаляю лише на наступний, пойнтери видаляться по 1 разу, інакше деструктор зациклиться
        delete next;
    }
};

template<class T>
struct Iter { // ітератор по нодах списку; перегрузка операторів !=, *, ++ необхідна, щоб працював range-based for loop
    // відповідно друкування списку буде виглядати як for (auto el: list) cout << el << ' ';
    DoublyLinkedNode<T> *node{}; // пойнтер на нод

    explicit Iter(DoublyLinkedNode<T> *n) : node{n} {} // explicit, бо 1 аргумент в конструкторі

    bool operator!=(const Iter &other) const noexcept { // порівнює з іншим ітератором (чи не дорівнює кінцю)
        return node != other.node;
    }

    T operator*() const noexcept { // перевантаження дереференсу для доступу до даних
        return node->data;
    };

    const Iter &operator++() noexcept { // перевантаження інкременту ітератора
        node = node->next;
        return *this; // заведено повертати значення при інкременті
    }

    ~Iter() { // деструктор
        delete node;
    }
};

template<class T>
class DoublyLinkedList { // сам двонапрямний список
private:
    DoublyLinkedNode<T> *head{}, *tail{}; // пойнтер на нод-початок і нод-кінець
    size_t n{}; // розмір

    void insertBefore(DoublyLinkedNode<T> *node, const T &new_data) { // вставлення нового ноду перед певним нодом
        auto newNode = new DoublyLinkedNode<T>(new_data, node, nullptr); // створення нового ноду з пойнтером на даний
        if (node->prev == nullptr) // якщо створюється перед першим нодом
            head = newNode;
        else { // зв'язування попереднього ноду з новим
            newNode->prev = node->prev;
            node->prev->next = newNode;
        }
        node->prev = newNode; // зв'язування даного ноду з новим
        ++n; // збільшення розміру
    }

    void insertAfter(DoublyLinkedNode<T> *node, const T &new_data) { // вставлення нового ноду після певного ноду
        auto newNode = new DoublyLinkedNode<T>(new_data, nullptr, node); // створення нового ноду з пойнтером на даний
        if (node->next == nullptr) // якщо створюється після останнього ноду
            tail = newNode;
        else { // зв'язування наступного ноду з новим
            newNode->next = node->next;
            node->next->prev = newNode;
        }
        node->next = newNode; // зв'язування даного ноду з новим
        ++n; // збільшення розміру
    }

    void remove(DoublyLinkedNode<T> *node) { // видалення певного ноду
        if (node->prev == nullptr) // якщо видаляється перший нод
            head = node->next;
        else
            node->prev->next = node->next; // зв'язування попереднього ноду з наступним
        if (node->next == nullptr)// якщо видаляється останній нод
            tail = node->prev;
        else // зв'язування наступного ноду з попереднім
            node->next->prev = node->prev;
        --n; // зменшення розміру
    }

public:
    DoublyLinkedList() = default; // стандартний конструктор

    DoublyLinkedList(const initializer_list<T> init) { // конструктор-ініціалізатор
        for (auto &el: init)
            this->push_back(el);
    }

    DoublyLinkedList(const DoublyLinkedList<T> &list) { // конструктор копіювання
        auto node = list.head;
        while (node != nullptr) { // проходження циклом по списку
            this->push_back(node->data);
            node = node->next; // аналог інкременту
        }
    }

    T at(const size_t pos) const { // доступ до елемента за позицією за O(n)
        if (pos >= n) // якщо позиція більша за розмір
            throw out_of_range("size is shorter");
        auto node = head;
        for (size_t i = 0; i < pos; ++i) // інкремент ноду pos разів
            node = node->next;
        return node->data;
    }

    Iter<T> begin() const noexcept { // ітератор на початок
        return Iter<T>(head);
    }

    Iter<T> end() const noexcept { // ітератор на кінець (tail->next)
        return Iter<T>(nullptr);
    }

    bool empty() noexcept { // перевірка чи пустий
        return head == nullptr;
    }

    size_t size() noexcept { // розмір
        return n;
    }

    T front() const noexcept { // доступ до першого елемента
        if (head == nullptr) {
            cout << "Error, list is empty" << endl;
            return T{};
        } else
            return head->data;
    }

    T back() const noexcept { // доступ до останнього елемента
        if (tail == nullptr) {
            cout << "Error, list is empty" << endl;
            return T{};
        } else
            return tail->data;
    }

    void push_front(const T &new_data) noexcept { // додати спереду
        if (head == nullptr) { // якщо список пустий
            head = tail = new DoublyLinkedNode<T>(new_data, nullptr, nullptr); // створення нового ноду
            ++n; // збільшення розміру
        } else
            insertBefore(head, new_data);
    }

    void push_back(const T &new_data) noexcept { // додати ззаду
        if (tail == nullptr) // якщо список пустий
            push_front(new_data);
        else
            insertAfter(tail, new_data);
    }

    void pop_front() noexcept { // видалити спереду
        if (head == nullptr) // якщо список пустий
            cout << "Error, list is empty" << endl;
        else
            remove(head);
    }

    void pop_back() noexcept { // видалити ззаду
        if (tail == nullptr) // якщо список пустий
            cout << "Error, list is empty" << endl;
        else
            remove(tail);
    }

    ~DoublyLinkedList() { // видаляю тільки перший, всі наступні видаляться деструкторами попередніх
        delete head;
    }
};

template<class T>
class Stack { // сам стек
private:
    DoublyLinkedList<T> container; // обгортає двонапрямний список
public:
    Stack() = default;

    bool empty() noexcept {
        return container.empty();
    }

    size_t size() noexcept {
        return container.size();
    }

    T top() const noexcept {
        return container.back();
    }

    void push(const T &new_data) noexcept {
        container.push_back(new_data);
    }

    void pop() noexcept {
        container.pop_back();
    }
};

#endif