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

    Shipping(size_t o, uint64_t t, Goods &g, Warehouse &wf, Warehouse &wt, Driver &d);

    size_t getOrder() const noexcept;

    void setOrder(size_t o);

    uint64_t getDuration() const noexcept;

    void setDuration(uint64_t d);

    Goods &getGoods() noexcept;

    void setGoods(const Goods &g);

    Warehouse &getWarehouseFrom() noexcept;

    void setWarehouseFrom(const Warehouse &w);

    Warehouse &getWarehouseTo() noexcept;

    void setWarehouseTo(const Warehouse &w);

    Driver &getDriver() noexcept;

    void setDriver(const Driver &d);

    string getStr() noexcept;
};

#endif
