#include "driver.h"

Driver::Driver() = default;

Driver::Driver(string_view n, string_view s, const uint64_t a) : name{n}, surname{s}, age{a} {}

string Driver::getName() const noexcept {
    return name;
}

void Driver::setName(string_view n) {
    name = n;
}

string Driver::getSurname() const noexcept {
    return surname;
}

void Driver::setSurname(string_view s) {
    surname = s;
}

uint64_t Driver::getAge() const noexcept {
    return age;
}

void Driver::setAge(const uint64_t a) {
    age = a;
}

string Driver::getStr() const noexcept {
    return format("{} {}, {} y.o.", getName(), getSurname(), getAge());
}
