#ifndef UNIVERSITY_GOODS_H
#define UNIVERSITY_GOODS_H

#include "shipping_member.h"
#include "goods_exception.h"

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

#endif
