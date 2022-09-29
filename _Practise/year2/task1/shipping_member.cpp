#include "shipping_member.h"

ShippingMember::ShippingMember() = default;

ShippingMember::ShippingMember(string_view name_) : name{name_} {}

string ShippingMember::getName() const noexcept {
    return name;
}

void ShippingMember::setName(string_view name_) noexcept {
    name = name_;
}

ostream &operator<<(ostream &os, const ShippingMember &obj) noexcept {
    os << obj.getStr();
    return os;
}

istream &operator>>(istream &is, ShippingMember &obj) {
    obj.input(is);
    return is;
}
