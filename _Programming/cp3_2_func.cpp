#include "cp3_2.h"

using namespace std;

Line::Line(ld a, ld b, ld c) : A{a}, B{b}, C{c} {}

void Line::print() const {
    cout << A << "x + " << B << "y + " << C << " = 0\n";
}

bool Line::isParallel(const Line &line) const {
    return this->A * line.B == line.A * this->B;
}

