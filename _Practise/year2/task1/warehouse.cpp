#include "warehouse.h"

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
