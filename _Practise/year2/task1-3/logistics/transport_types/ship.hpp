#ifndef UNIVERSITY_SHIP_HPP
#define UNIVERSITY_SHIP_HPP

#include <string>

#include "../../logistics/factory/transport_interface.hpp"
#include "../../logistics/shipping_members/shipping_member.hpp"

using namespace std;

class Ship : virtual public NamedObject, virtual public ITransport {
public:
    Ship() : NamedObject{"Ship"} {}

    string getType() const noexcept override {
        return getName();
    }

    string deliver() const noexcept override {
        return "Delivered by ship.";
    }
};

#endif
