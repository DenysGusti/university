#ifndef UNIVERSITY_PLANE_H
#define UNIVERSITY_PLANE_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Plane {
private:
    char name[100]{}, brand[100]{};
    uint64_t capacity{}, engine_displacement{};
    bool autopilot_available{};

public:
    Plane() = default;

    Plane(const char *name_, const char *brand_,
          const uint64_t capacity_, const uint64_t engine_displacement_, const bool autopilot_available_);

    bool hasAutopilot() const noexcept;

    friend ostream &operator<<(ostream &os, const Plane &obj);

    friend istream &operator>>(istream &is, Plane &obj);
};

#endif
