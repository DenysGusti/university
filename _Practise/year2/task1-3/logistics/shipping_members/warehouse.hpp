#ifndef UNIVERSITY_WAREHOUSE_H
#define UNIVERSITY_WAREHOUSE_H

#include "shipping_member.hpp"

class Warehouse : public ShippingMember {
private:
    string city;
    ld capacity{};

public:
    Warehouse();

    Warehouse(string_view name_, string_view city_, ld capacity_);

    string getCity() const noexcept;

    void setCity(string_view city_);

    ld getCapacity() const noexcept;

    void setCapacity(ld capacity_);

    string getStr() const noexcept override;

    void input(istream &is) override;
};

Warehouse::Warehouse() = default;

Warehouse::Warehouse(string_view name_, string_view city_, const ld capacity_) : ShippingMember{name_}, city{city_},
                                                                                 capacity{capacity_} {}

string Warehouse::getCity() const noexcept {
    return city;
}

void Warehouse::setCity(string_view city_) {
    city = city_;
}

ld Warehouse::getCapacity() const noexcept {
    return capacity;
}

void Warehouse::setCapacity(const ld capacity_) {
    capacity = capacity_;
}

string Warehouse::getStr() const noexcept {
    return format("{}, {}, {}t", getName(), getCity(), getCapacity());
}

void Warehouse::input(istream &is) {
    if (&is == &cin)
        cout << "Enter warehouse name, city and capacity, t:" << endl;

    is >> name >> city >> capacity;
}

#endif
