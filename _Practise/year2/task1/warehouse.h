#ifndef UNIVERSITY_WAREHOUSE_H
#define UNIVERSITY_WAREHOUSE_H

#include <string>
#include <format>

using namespace std;
using ld = long double;

class Warehouse {
private:
    string name, city;
    ld capacity{};

public:
    Warehouse();

    Warehouse(string_view n, string_view s, ld c);

    string getName() const noexcept;

    void setName(string_view n);

    string getCity() const noexcept;

    void setCity(string_view s);

    ld getCapacity() const noexcept;

    void setCapacity(ld c);

    string getStr() const noexcept;
};

#endif
