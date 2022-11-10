#ifndef UNIVERSITY_SHIPPING_MEMBER_H
#define UNIVERSITY_SHIPPING_MEMBER_H

#include <iostream>
#include <string>
#include <format>

#include "../../logistics/named_object.hpp"

using namespace std;
using ld = long double;

class ShippingMember: public NamedObject {
public:
    ShippingMember();

    ~ShippingMember() override;

    explicit ShippingMember(string_view name_);

    virtual string getStr() const noexcept = 0;

    virtual void input(istream &is) = 0;

    friend ostream &operator<<(ostream &os, const ShippingMember &obj) noexcept;

    friend istream &operator>>(istream &is, ShippingMember &obj);
};

ShippingMember::ShippingMember() = default;

ShippingMember::~ShippingMember() = default;

ShippingMember::ShippingMember(string_view name_) : NamedObject{name_} {}

ostream &operator<<(ostream &os, const ShippingMember &obj) noexcept {
    os << obj.getStr();
    return os;
}

istream &operator>>(istream &is, ShippingMember &obj) {
    obj.input(is);
    return is;
}

#endif
