#ifndef UNIVERSITY_DYNAMIC_LIST_HPP
#define UNIVERSITY_DYNAMIC_LIST_HPP

#include "printable_list.hpp"

class IDynamicList : virtual public IPrintableList {
public:
    ~IDynamicList() override = default;

    virtual size_t getSize() const noexcept = 0;

    virtual void addNewFromTerminal() = 0;

    virtual void addNewFromFile() = 0;

    virtual void deleteFirst() = 0;

    virtual void deleteLast() = 0;
};

#endif
