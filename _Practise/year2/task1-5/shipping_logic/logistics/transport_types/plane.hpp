#ifndef UNIVERSITY_PLANE_HPP
#define UNIVERSITY_PLANE_HPP

#include "../../logistics/factory/transport_interface.hpp"
#include "../../logistics/shipping_members/shipping_member.hpp"

using namespace std;

class Plane : virtual public NamedObject, virtual public ITransport {
public:
    Plane() : NamedObject{"Plane"} {}

    string getType() const noexcept override {
        return getName();
    }

    string deliver() const noexcept override {
        return "Delivered by ship.";
    }
};

#endif
