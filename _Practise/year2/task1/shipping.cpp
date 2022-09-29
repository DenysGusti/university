#include "shipping.h"

#include <utility>

Shipping::Shipping() = default;

Shipping::Shipping(size_t order_, uint64_t duration_, Goods &goods_, Warehouse &warehouseFrom_, Warehouse &warehouseTo_,
                   Driver &driver_)
        : order{order_}, duration{duration_}, goods{goods_}, warehouseFrom{warehouseFrom_}, warehouseTo{warehouseTo_},
          driver{driver_} {}

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

string Shipping::getStr() noexcept {
    return format("№{} goods: {}; from: {}; to: {}; driver: {}; duration: {} days", getOrder(), goods.getStr(),
                  warehouseFrom.getStr(), warehouseTo.getStr(), driver.getStr(), getDuration());
}
