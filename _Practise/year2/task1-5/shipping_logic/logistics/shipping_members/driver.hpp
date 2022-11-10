#ifndef UNIVERSITY_DRIVER_H
#define UNIVERSITY_DRIVER_H

#include "shipping_member.hpp"

class Driver: public ShippingMember {
private:
    string surname;
    uint64_t age{};

public:
    Driver();

    Driver(string_view name_, string_view surname_, uint64_t age_);

    string getSurname() const noexcept;

    void setSurname(string_view surname_);

    uint64_t getAge() const noexcept;

    void setAge(uint64_t age_);

    string getStr() const noexcept override;

    string getRepr() const noexcept override;

    void input(istream &is) override;
};

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

void Driver::input(istream &is) {
    if (&is == &cin)
        cout << "Enter driver's name, surname, age:" << endl;

    is >> name >> surname >> age;
}

string Driver::getRepr() const noexcept {
    return format("{} {} {}", getName(), getSurname(), getAge());
}

#endif
