#include "warehouse.h"

Warehouse::Warehouse() = default;

Warehouse::Warehouse(string_view n, string_view s, const ld c) : name{n}, city{s}, capacity{c} {}

string Warehouse::getName() const noexcept {
    return name;
}

void Warehouse::setName(string_view n) {
    name = n;
}

string Warehouse::getCity() const noexcept {
    return city;
}

void Warehouse::setCity(string_view c) {
    city = c;
}

ld Warehouse::getCapacity() const noexcept {
    return capacity;
}

void Warehouse::setCapacity(const ld c) {
    capacity = c;
}

string Warehouse::getStr() const noexcept {
    return format("{}, {}, {}t", getName(), getCity(), getCapacity());
}
