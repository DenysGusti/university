#include "shipping_member.h"

ShippingMember::ShippingMember() = default;

ShippingMember::ShippingMember(string_view name_) : name{name_} {}

string ShippingMember::getName() const noexcept {
    return name;
}

void ShippingMember::setName(string_view name_) noexcept {
    name = name_;
}
