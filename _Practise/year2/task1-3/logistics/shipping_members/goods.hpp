#ifndef UNIVERSITY_GOODS_H
#define UNIVERSITY_GOODS_H

#include "shipping_member.hpp"
#include "../../exceptions/goods_exception.hpp"

class Goods: public ShippingMember {
private:
    ld quantity{};

public:
    Goods() = default;

    Goods(string_view name_, ld quantity_);

    ld getQuantity() const noexcept;

    void setQuantity(ld quantity_);

    string getStr() const noexcept override;

    Goods &operator+=(const Goods &other);

    void input(istream &is) override;
};

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

void Goods::input(istream &is) {
    if (&is == &cin)
        cout << "Enter goods name and quantity, t:" << endl;

    is >> name >> quantity;
}

#endif
