#include "driver.h"

Driver::Driver() = default;

Driver::Driver(string_view name_, string_view surname_, const uint64_t age_) : ShippingMember{name_}, surname{surname_},
                                                                               age{age_} {}

string Driver::getSurname() const noexcept {
    return surname;
}

void Driver::setSurname(string_view surname_) {
    surname = surname_;
}

uint64_t Driver::getAge() const noexcept {
    return age;
}

void Driver::setAge(const uint64_t age_) {
    age = age_;
}

string Driver::getStr() const noexcept {
    return format("{} {}, {} y.o.", getName(), getSurname(), getAge());
}
