#ifndef UNIVERSITY_MY_LIST_HPP
#define UNIVERSITY_MY_LIST_HPP

#include <deque>
#include <functional>
#include <ranges>

#include "dynamic_list.hpp"

using namespace std;

template<class T>
class MyList : virtual public IDynamicList, virtual public IPrintableList {
protected:
    deque<T> objects;

public:
    ~MyList() override = default;

    void sortAll(const function<bool(const T &, const T &)> &func) noexcept {
        ranges::sort(objects, func);
    };
};

#endif
