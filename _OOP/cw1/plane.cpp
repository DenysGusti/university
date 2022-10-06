#include "plane.h"

Plane::Plane(const char *name_, const char *brand_,
             const uint64_t capacity_, const uint64_t engine_displacement_, const bool autopilot_available_)
        : capacity{capacity_}, engine_displacement{engine_displacement_},
          autopilot_available{autopilot_available_} {
    strcpy_s(name, name_);
    strcpy_s(brand, brand_);
}

bool Plane::hasAutopilot() const noexcept {
    return autopilot_available;
}

ostream &operator<<(ostream &os, const Plane &obj) {
    os << boolalpha << "name: " << obj.name << "; brand: " << obj.brand << "; capacity: " << obj.capacity <<
       "; engine displacement: " << obj.engine_displacement << "; autopilot available: " << obj.autopilot_available
       << ";";
    return os;
}

istream &operator>>(istream &is, Plane &obj) {
    char tmp[100]{};

    if (&is == &cin)
        cout << "Enter name: ";
    is >> tmp;
    strcpy_s(obj.name, tmp);

    if (&is == &cin)
        cout << "Enter brand: ";
    is >> tmp;
    strcpy_s(obj.brand, tmp);

    if (&is == &cin)
        cout << "Enter capacity: ";
    is >> obj.capacity;

    if (&is == &cin)
        cout << "Enter engine displacement: ";
    is >> obj.engine_displacement;

    if (&is == &cin)
        cout << "Enter if autopilot available (0 or 1): ";
    is >> obj.autopilot_available;
    return is;
}
