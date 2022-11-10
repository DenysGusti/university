#ifndef UNIVERSITY_SHIPPING_H
#define UNIVERSITY_SHIPPING_H

#include <string>
#include <format>
#include <vector>

#include "shipping_members/goods.hpp"
#include "shipping_members/warehouse.hpp"
#include "shipping_members/driver.hpp"
#include "factory/shipping_factory.hpp"

using namespace std;

class Shipping {
private:
    size_t order{};
    uint64_t duration{};
    Goods goods;
    Warehouse warehouseFrom, warehouseTo;
    Driver driver;

    shared_ptr<ShippingFactory> factory;
    shared_ptr<ITransport> transport;

public:
    Shipping();

    Shipping(size_t order_, uint64_t duration_, Goods &goods_, Warehouse &warehouseFrom_, Warehouse &warehouseTo_,
             Driver &driver_, const shared_ptr<ShippingFactory> &factory_);

    size_t getOrder() const noexcept;

    void setOrder(size_t order_);

    uint64_t getDuration() const noexcept;

    void setDuration(uint64_t duration_);

    Goods &getGoods() noexcept;

    void setGoods(const Goods &goods_);

    Warehouse &getWarehouseFrom() noexcept;

    void setWarehouseFrom(const Warehouse &warehouseFrom_);

    Warehouse &getWarehouseTo() noexcept;

    void setWarehouseTo(const Warehouse &warehouseTo_);

    Driver &getDriver() noexcept;

    void setDriver(const Driver &driver_);

    string getStr() const noexcept;

    friend ostream &operator<<(ostream &os, const Shipping &obj) noexcept;

    void setFactory(const shared_ptr<ShippingFactory> &factory_);

    shared_ptr<ShippingFactory> getFactory();

    void createTransport();

    string deliver() const noexcept;

    string getSpecies() const;

    string getRepr() const noexcept;
};

Shipping::Shipping() = default;

Shipping::Shipping(size_t order_, uint64_t duration_, Goods &goods_, Warehouse &warehouseFrom_, Warehouse &warehouseTo_,
                   Driver &driver_, const shared_ptr<ShippingFactory> &factory_)
        : order{order_}, duration{duration_}, goods{goods_}, warehouseFrom{warehouseFrom_}, warehouseTo{warehouseTo_},
          driver{driver_}, factory{factory_} {
    createTransport();
}

size_t Shipping::getOrder() const noexcept {
    return order;
}

void Shipping::setOrder(const size_t order_) {
    order = order_;
}

uint64_t Shipping::getDuration() const noexcept {
    return duration;
}

void Shipping::setDuration(const uint64_t duration_) {
    duration = duration_;
}

Goods &Shipping::getGoods() noexcept {
    return goods;
}

void Shipping::setGoods(const Goods &goods_) {
    goods = goods_;
}

Warehouse &Shipping::getWarehouseFrom() noexcept {
    return warehouseFrom;
}

void Shipping::setWarehouseFrom(const Warehouse &warehouseFrom_) {
    warehouseFrom = warehouseFrom_;
}

Warehouse &Shipping::getWarehouseTo() noexcept {
    return warehouseFrom;
}

void Shipping::setWarehouseTo(const Warehouse &warehouseTo_) {
    warehouseTo = warehouseTo_;
}

Driver &Shipping::getDriver() noexcept {
    return driver;
}

void Shipping::setDriver(const Driver &driver_) {
    driver = driver_;
}

string Shipping::getStr() const noexcept {
    return format("№{} goods: {}; from: {}; to: {}; driver: {}; duration: {} days; transport: {}", getOrder(),
                  goods.getStr(), warehouseFrom.getStr(), warehouseTo.getStr(), driver.getStr(), getDuration(),
                  transport->getType());
}

ostream &operator<<(ostream &os, const Shipping &obj) noexcept {
    os << obj.getStr();
    return os;
}

void Shipping::createTransport() {
    transport = factory->createTransport();
}

string Shipping::deliver() const noexcept {
    return transport->deliver();
}

void Shipping::setFactory(const shared_ptr<ShippingFactory> &factory_) {
    factory = factory_;
}

shared_ptr<ShippingFactory> Shipping::getFactory() {
    return factory;
}

string Shipping::getSpecies() const  {
    if (transport->getType() == "Ship")
        return "sea";
    if (transport->getType() == "Truck")
        return "road";
    if (transport->getType() == "Train")
        return "rail";
    if (transport->getType() == "Plane")
        return "air";

    throw exception("unexpected type");
}

string Shipping::getRepr() const noexcept {
    return format("{} {} {} {} {} {} {}", getOrder(), goods.getRepr(), warehouseFrom.getRepr(), warehouseTo.getRepr(),
                  driver.getRepr(), getDuration(), getSpecies());
}

#endif
