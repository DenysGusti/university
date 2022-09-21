#include "goods.h"

Goods::Goods() = default;

Goods::Goods(string_view n, const ld q) : name{n}, quantity{q} {}

string Goods::getName() const noexcept {
    return name;
}

void Goods::setName(string_view n) {
    name = n;
}

ld Goods::getQuantity() const noexcept {
    return quantity;
}

void Goods::setQuantity(ld q) {
    quantity = q;
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
}
