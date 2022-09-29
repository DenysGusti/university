#ifndef UNIVERSITY_SHIPPING_H
#define UNIVERSITY_SHIPPING_H

#include <string>
#include <format>
#include <vector>

#include "goods.h"
#include "warehouse.h"
#include "driver.h"

using namespace std;

class Shipping {
private:
    size_t order{};
    uint64_t duration{};
    Goods goods;
    Warehouse warehouseFrom, warehouseTo;
    Driver driver;

public:
    Shipping();

    Shipping(size_t order_, uint64_t duration_, Goods &goods_, Warehouse &warehouseFrom_, Warehouse &warehouseTo_,
             Driver &driver_);

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
};

#endif
