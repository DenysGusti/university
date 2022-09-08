#ifndef UNIVERSITY_DATE_H
#define UNIVERSITY_DATE_H

#include <iostream>
#include <string>
#include <format>

using namespace std;

class Date {
private:
    uint16_t day{}, month{}, year{};

public:
    Date() = default;

    Date(const uint16_t d, const uint16_t m, const uint16_t y) : day{d}, month{m}, year{y} {
        if (day == 0 || day > 12 || month == 0 || month > 12)
            throw invalid_argument("Date format is wrong! " + printDate());
    }

    string printDate() const noexcept {
        return format("{:0>2}.{:0>2}.{:0>4}", day, month, year);
    }

    uint16_t getYear() const noexcept {
        return year;
    }

    static uint16_t getCurrentYear() noexcept {
        return 2022;
    }
};

#endif
