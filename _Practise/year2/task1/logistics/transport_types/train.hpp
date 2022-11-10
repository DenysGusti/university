#ifndef UNIVERSITY_TRAIN_HPP
#define UNIVERSITY_TRAIN_HPP

#include "../../logistics/factory/transport_interface.hpp"
#include "../../logistics/shipping_members/shipping_member.hpp"

using namespace std;

class Train : virtual public NamedObject, virtual public ITransport {
public:
    Train() : NamedObject{"Train"} {}

    string getType() const noexcept override {
        return getName();
    }

    string deliver() const noexcept override {
        return "Delivered by ship.";
    }
};

#endif
