#ifndef UNIVERSITY_DRIVER_H
#define UNIVERSITY_DRIVER_H

#include "shipping_member.h"

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

    void input(istream &is) override;
};

#endif
