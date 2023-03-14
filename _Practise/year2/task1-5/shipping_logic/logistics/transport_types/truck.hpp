#ifndef UNIVERSITY_TRUCK_HPP
#define UNIVERSITY_TRUCK_HPP

#include <string>

#include "../../logistics/factory/transport_interface.hpp"
#include "../../logistics/shipping_members/shipping_member.hpp"

using namespace std;

class Truck : virtual public NamedObject, virtual public ITransport {
public:
    Truck() : NamedObject{"Truck"} {}

    string getType() const noexcept override {
        return getName();
    }

    string deliver() const noexcept override {
        return "Delivered by truck.";
    }
};

#endif
