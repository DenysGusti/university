#ifndef UNIVERSITY_CP3_2_H
#define UNIVERSITY_CP3_2_H

#include <iostream>

using ld = long double;

struct Line {
    long double A{}, B{}, C{};

    Line(ld a, ld b, ld c);

    void print() const;

    bool isParallel(const Line &line) const; // ті, що збігаються - паралельні
};

#endif //UNIVERSITY_CP3_2_H
