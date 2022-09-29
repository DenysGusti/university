#ifndef UNIVERSITY_SHIPPING_MEMBER_H
#define UNIVERSITY_SHIPPING_MEMBER_H

#include <iostream>
#include <string>
#include <format>

using namespace std;
using ld = long double;

class ShippingMember {
protected:
    string name;

public:
    ShippingMember();

    explicit ShippingMember(string_view name_);

    string getName() const noexcept;

    void setName(string_view name_) noexcept;

    virtual string getStr() const noexcept = 0;

    friend ostream &operator<<(ostream &os, const ShippingMember &obj) noexcept;
};

#endif
