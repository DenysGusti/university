#ifndef UNTITLED_TASK_9_5_H
#define UNTITLED_TASK_9_5_H

#include <iostream>

using namespace std;

template<class T>
struct DoublyLinkedNode {
public:
    T data{};
    DoublyLinkedNode *next{}, *prev{};

    DoublyLinkedNode(const T d, DoublyLinkedNode<T> *n, DoublyLinkedNode<T> *p) : data{d}, next{n}, prev{p} {};

    ~DoublyLinkedNode() {
        // cout << "DoublyLinkedNode destructor " << data << endl;
        delete next;
    }
};

template<class T>
class DoublyLinkedList {
private:
    DoublyLinkedNode<T> *head{}, *tail{};
    size_t n{};

    void insertBefore(DoublyLinkedNode<T> *node, const T &new_data) {
        auto newNode = new DoublyLinkedNode<T>(new_data, node, nullptr);
        if (node->prev == nullptr)
            head = newNode;
        else {
            newNode->prev = node->prev;
            node->prev->next = newNode;
        }
        node->prev = newNode;
        ++n;
    };

    void insertAfter(DoublyLinkedNode<T> *node, const T &new_data) {
        auto newNode = new DoublyLinkedNode<T>(new_data, nullptr, node);
        if (node->next == nullptr)
            tail = newNode;
        else {
            newNode->next = node->next;
            node->next->prev = newNode;
        }
        node->next = newNode;
        ++n;
    };

    void remove(DoublyLinkedNode<T> *node) {
        if (node->prev == nullptr)
            head = node->next;
        else
            node->prev->next = node->next;
        if (node->next == nullptr)
            tail = node->prev;
        else
            node->next->prev = node->prev;
        --n;
    }

public:
    DoublyLinkedList() = default;

    DoublyLinkedList(initializer_list<T> init) {
        for (const auto &el: init)
            this->push_back(el);
        cout << "Initializer constructor" << endl;
    };

    DoublyLinkedList(const DoublyLinkedList<T> &list) {
        auto node = list.head;
        while (node != nullptr) {
            this->push_back(node->data);
            node = node->next;
        }
        cout << "Copy constructor" << endl;
    };

    bool empty() noexcept {
        return head == nullptr;
    };

    size_t size() noexcept {
        return n;
    };

    void print() {
        auto node = head;
        while (node != nullptr) {
            cout << node->data << ' ';
            node = node->next;
        }
        cout << '\n';
    }

    T front() noexcept {
        if (head == nullptr) {
            cout << "Error, list is empty" << endl;
            return T{};
        } else
            return head->data;
    }

    T back() noexcept {
        if (tail == nullptr) {
            cout << "Error, list is empty" << endl;
            return T{};
        } else
            return tail->data;
    }

    void push_front(const T &new_data) noexcept {
        if (head == nullptr) {
            head = tail = new DoublyLinkedNode<T>(new_data, nullptr, nullptr);
            ++n;
        } else
            insertBefore(head, new_data);
    };

    void push_back(const T &new_data) noexcept {
        if (tail == nullptr)
            push_front(new_data);
        else
            insertAfter(tail, new_data);
    };

    void pop_front() noexcept {
        if (head == nullptr)
            cout << "Error, list is empty" << endl;
        else
            remove(head);
    };

    void pop_back() noexcept {
        if (tail == nullptr)
            cout << "Error, list is empty" << endl;
        else
            remove(tail);
    };

    ~DoublyLinkedList() {
        // cout << "DoublyLinkedList destructor" << endl;
        delete head;
    }
};

template<class T>
class Stack {
private:
    DoublyLinkedList<T> container{};
public:
    Stack() = default;

    bool empty() noexcept {
        return container.empty();
    };

    size_t size() noexcept {
        return container.size();
    };

    T top() noexcept {
        return container.back();
    };

    void push(const T &new_data) noexcept {
        container.push_back(new_data);
    };

    void pop() noexcept {
        container.pop_back();
    };
};

#endif