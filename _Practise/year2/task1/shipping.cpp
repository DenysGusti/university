#include "shipping.h"

#include <utility>

Shipping::Shipping() = default;

Shipping::Shipping(size_t o, uint64_t t, Goods &g, Warehouse &wf, Warehouse &wt, Driver &d)
        : order{o}, duration{t},
          goods{std::move(g)}, warehouseFrom{std::move(wf)}, warehouseTo{std::move(wt)}, driver{std::move(d)} {}

size_t Shipping::getOrder() const noexcept {
    return order;
}

void Shipping::setOrder(const size_t o) {
    order = o;
}

uint64_t Shipping::getDuration() const noexcept {
    return duration;
}

void Shipping::setDuration(const uint64_t d) {
    duration = d;
}

Goods &Shipping::getGoods() noexcept {
    return goods;
}

void Shipping::setGoods(const Goods &g) {
    goods = g;
}

Warehouse &Shipping::getWarehouseFrom() noexcept {
    return warehouseFrom;
}

void Shipping::setWarehouseFrom(const Warehouse &w) {
    warehouseFrom = w;
}

Warehouse &Shipping::getWarehouseTo() noexcept {
    return warehouseFrom;
}

void Shipping::setWarehouseTo(const Warehouse &w) {
    warehouseFrom = w;
}

Driver &Shipping::getDriver() noexcept {
    return driver;
}

void Shipping::setDriver(const Driver &d) {
    driver = d;
}

string Shipping::getStr() noexcept {
    return format("№{} goods: {}; from: {}; to: {}; driver: {}; duration: {} days", getOrder(), goods.getStr(),
                  warehouseFrom.getStr(), warehouseTo.getStr(), driver.getStr(), getDuration());
}
