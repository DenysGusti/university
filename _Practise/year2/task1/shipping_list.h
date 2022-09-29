#ifndef UNIVERSITY_SHIPPING_LIST_H
#define UNIVERSITY_SHIPPING_LIST_H

#include <memory>
#include <ranges>
#include <deque>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <functional>

#include "shipping.h"

using namespace std;
namespace rv = ranges::views;

class ShippingList {
private:
    filesystem::path in_file, out_file;

    deque<unique_ptr<Shipping>> shippings;

    void printAllShippings(ostream &out, bool reversed) const;

    Shipping getShipping(istream &in);

    void printOnly(string_view dataType, ostream &out, bool reversed) const;

public:

    ShippingList(string_view in, string_view out);

    size_t getSize() const noexcept;

    void addNewShippingFromTerminal();

    void addNewShippingFromFile();

    void deleteFirstShipping();

    void deleteLastShipping();

    void printAllShippingsToTerminal(bool reversed) const;

    void printAllShippingsToFile(bool reversed) const;

    void sortAllShippings(const function<bool(const unique_ptr<Shipping> &, const unique_ptr<Shipping> &)> &func);

    void printOnlyToTerminal(string_view dataType, bool reversed) const;

    void printOnlyToFile(string_view dataType, bool reversed) const;

    ShippingList &operator+=(const Shipping &newShipping);
};

#endif