#include "goods.h"

Goods::Goods(string_view name_, const ld quantity_) : ShippingMember{name_}, quantity{quantity_} {}

ld Goods::getQuantity() const noexcept {
    return quantity;
}

void Goods::setQuantity(const ld quantity_) {
    quantity = quantity_;
}

string Goods::getStr() const noexcept {
    return format("{}, {}t", getName(), getQuantity());
}

Goods &Goods::operator+=(const Goods &other) {
    if (!name.empty() && name != other.name)
        throw GoodsException("Impossible to add goods with different names!");

    if (name.empty())
        name = other.name;

    quantity += other.quantity;

    return *this;
}
