#ifndef UNIVERSITY_DRIVER_H
#define UNIVERSITY_DRIVER_H

#include <string>
#include <format>

using namespace std;
using ld = long double;

class Driver {
private:
    string name, surname;
    uint64_t age{};

public:
    Driver();

    Driver(string_view n, string_view s, uint64_t a);

    string getName() const noexcept;

    void setName(string_view n);

    string getSurname() const noexcept;

    void setSurname(string_view s);

    uint64_t getAge() const noexcept;

    void setAge(uint64_t a);

    string getStr() const noexcept;
};


#endif
