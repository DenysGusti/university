#ifndef UNIVERSITY_CW3_TASK_3_6_H
#define UNIVERSITY_CW3_TASK_3_6_H

#include <iostream>
#include <cmath>

using namespace std;

struct Complex {
    double a{}, b{};

    Complex(double aa, double bb);

    void print() const;

    double module();
};

Complex::Complex(double aa, double bb) : a{aa}, b{bb} {}

void Complex::print() const {
    cout << a << "i+" << b;
}

double Complex::module() {
    return hypot(a, b);
}

#endif
