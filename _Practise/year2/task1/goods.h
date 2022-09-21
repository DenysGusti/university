#ifndef UNIVERSITY_GOODS_H
#define UNIVERSITY_GOODS_H

#include <string>
#include <format>

#include "goods_exception.h"

using namespace std;
using ld = long double;

class Goods {
private:
    string name;
    ld quantity{};

public:
    Goods();

    Goods(string_view n, ld q);

    string getName() const noexcept;

    void setName(string_view n);

    ld getQuantity() const noexcept;

    void setQuantity(ld q);

    string getStr() const noexcept;

    Goods &operator+=(const Goods &other);
};

#endif
