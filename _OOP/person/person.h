#ifndef UNIVERSITY_PERSON_H
#define UNIVERSITY_PERSON_H

#include <iostream>
#include <string>

#include "date.h"

using namespace std;

class Person {
    string firstName{}, lastName{};
    Date birthdate{};

public:
    Person(string_view fn, string_view ln, const Date &d) : firstName{fn}, lastName{ln}, birthdate{d} {}

    void WriteToConsole() const noexcept {
        cout << firstName << ' ' << lastName << ' ' << birthdate.printDate() << '\n';
    }

    static int maxAge() noexcept {
        return 120;
    }

    uint16_t getAge() const noexcept {
        return Date::getCurrentYear() - birthdate.getYear();
    }
};

#endif
