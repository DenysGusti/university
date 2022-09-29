#ifndef UNIVERSITY_WAREHOUSE_H
#define UNIVERSITY_WAREHOUSE_H

#include "shipping_member.h"

class Warehouse : public ShippingMember {
private:
    string city;
    ld capacity{};

public:
    Warehouse();

    Warehouse(string_view name_, string_view city_, ld capacity_);

    string getCity() const noexcept;

    void setCity(string_view city_);

    ld getCapacity() const noexcept;

    void setCapacity(ld capacity_);

    string getStr() const noexcept override;
};

#endif
