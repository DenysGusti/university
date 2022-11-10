#ifndef UNIVERSITY_SHIPPING_FACTORY_HPP
#define UNIVERSITY_SHIPPING_FACTORY_HPP

#include <memory>

#include "../../logistics/transport_types/plane.hpp"
#include "../../logistics/transport_types/ship.hpp"
#include "../../logistics/transport_types/train.hpp"
#include "../../logistics/transport_types/truck.hpp"

using namespace std;

class ShippingFactory {
public:
    virtual ~ShippingFactory() = default;

    virtual unique_ptr<ITransport> createTransport() const noexcept = 0;
};

class SeaShippingFactory : public ShippingFactory {
public:
    unique_ptr<ITransport> createTransport() const noexcept override {
        return make_unique<Ship>();
    }
};

class RoadShippingFactory : public ShippingFactory {
public:
    unique_ptr<ITransport> createTransport() const noexcept override {
        return make_unique<Truck>();
    }
};

class RailShippingFactory : public ShippingFactory {
public:
    unique_ptr<ITransport> createTransport() const noexcept override {
        return make_unique<Train>();
    }
};

class AirShippingFactory : public ShippingFactory {
public:
    unique_ptr<ITransport> createTransport() const noexcept override {
        return make_unique<Plane>();
    }
};

#endif
