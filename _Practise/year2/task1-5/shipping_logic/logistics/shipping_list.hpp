#ifndef UNIVERSITY_SHIPPING_LIST_H
#define UNIVERSITY_SHIPPING_LIST_H

#include <memory>
#include <ranges>
#include <deque>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <functional>

#include "shipping.hpp"
#include "list_interfaces/my_list.hpp"

using namespace std;
namespace rv = ranges::views;

class ShippingList : public MyList<unique_ptr<Shipping> >, virtual public IDynamicList, virtual public IPrintableList {
private:
    filesystem::path in_file, out_file;

    void printAll(ostream &out, bool reversed) const noexcept;

    Shipping getShipping(istream &in);

    void printOnly(string_view dataType, ostream &out, bool reversed) const noexcept;

    static unique_ptr<ShippingFactory> configureFactory(string_view type);

public:
    ShippingList(string_view in, string_view out);

    [[nodiscard]] size_t getSize() const noexcept override;

    void addNewFromTerminal() override;

    void addNewFromFile() override;

    void deleteFirst() override;

    void deleteLast() override;

    void printAllToTerminal(bool reversed) const noexcept override;

    void printAllToFile(bool reversed) const noexcept override;

    void printOnlyToTerminal(string_view dataType, bool reversed) const;

    void printOnlyToFile(string_view dataType, bool reversed) const;

    ShippingList &operator+=(const Shipping &newShipping);

    void updateFile() const noexcept;
};

ShippingList::ShippingList(string_view in, string_view out) : in_file{in}, out_file{out} {}

void ShippingList::deleteFirst() {
    if (objects.empty())
        throw out_of_range("Trying to delete element from empty shipping array!");

    objects.pop_front();
}

void ShippingList::deleteLast() {
    if (objects.empty())
        throw out_of_range("Trying to delete element from empty shipping array!");

    objects.pop_back();
}

void ShippingList::printAll(ostream &out, const bool reversed) const noexcept {
    if (!reversed)
        for (const auto &pShipping: objects)
            out << *pShipping << '\n';

    else
        for (const auto &pShipping: objects | rv::reverse)
            out << *pShipping << '\n';

    out << '\n';
}

void ShippingList::printAllToTerminal(const bool reversed) const noexcept {
    printAll(cout, reversed);
}

void ShippingList::printAllToFile(const bool reversed) const noexcept {
    ofstream fout{out_file, ios::app};
    printAll(fout, reversed);
}

unique_ptr<ShippingFactory> ShippingList::configureFactory(string_view type) {
    if (type == "sea")
        return make_unique<SeaShippingFactory>();
    if (type == "road")
        return make_unique<RoadShippingFactory>();
    if (type == "rail")
        return make_unique<RailShippingFactory>();
    if (type == "air")
        return make_unique<AirShippingFactory>();

    throw exception("unknown shipping type");
}

Shipping ShippingList::getShipping(istream &in) {
    size_t n{};
    uint64_t duration{};
    Goods g;
    Warehouse wf, wt;
    Driver d;
    string type;

    if (&in != &cin)
        in >> n;

    in >> g;

    if (&in == &cin)
        cout << "Departure warehouse:" << endl;
    in >> wf;

    if (&in == &cin)
        cout << "Destination warehouse:" << endl;
    in >> wt;

    in >> d;

    if (&in == &cin)
        cout << "Enter duration, days:" << endl;
    in >> duration;

    if (&in == &cin)
        cout << "Enter shipping type: " << endl;
    in >> type;

    shared_ptr<ShippingFactory> factory = configureFactory(type);

    return {&in == &cin ? objects.size() + 1 : n, duration, g, wf, wt, d, factory};
}

void ShippingList::addNewFromTerminal() {
    objects.push_back(make_unique<Shipping>(getShipping(cin)));
}

void ShippingList::addNewFromFile() {
    objects.clear();
    for (ifstream fin{in_file}; !fin.eof(); objects.push_back(make_unique<Shipping>(getShipping(fin))));
}

void ShippingList::printOnlyToTerminal(string_view dataType, bool reversed) const {
    printOnly(dataType, cout, reversed);
}

void ShippingList::printOnlyToFile(string_view dataType, bool reversed) const {
    ofstream fout{out_file, ios::app};
    printOnly(dataType, fout, reversed);
}

void ShippingList::printOnly(string_view dataType, ostream &out, bool reversed) const noexcept {
    if (!reversed)
        for (const auto &pShipping: objects) {
            if (dataType == "goods")
                out << pShipping->getGoods() << '\n';
            else if (dataType == "departure warehouses")
                out << pShipping->getWarehouseFrom() << '\n';
            else if (dataType == "destination warehouses")
                out << pShipping->getWarehouseTo() << '\n';
            else if (dataType == "drivers")
                out << pShipping->getDriver() << '\n';
        }
    else
        for (const auto &pShipping: objects | rv::reverse) {
            if (dataType == "goods")
                out << pShipping->getGoods() << '\n';
            else if (dataType == "departure warehouses")
                out << pShipping->getWarehouseFrom() << '\n';
            else if (dataType == "destination warehouses")
                out << pShipping->getWarehouseTo() << '\n';
            else if (dataType == "drivers")
                out << pShipping->getDriver() << '\n';
        }

    out << '\n';
}

size_t ShippingList::getSize() const noexcept {
    return objects.size();
}

ShippingList &ShippingList::operator+=(const Shipping &newShipping) {
    objects.push_back(make_unique<Shipping>(newShipping));
    return *this;
}

void ShippingList::updateFile() const noexcept {
    for (ofstream out{in_file}; const auto &pShipping: objects) {
        out << pShipping->getRepr();
        if (&pShipping != &objects.back())
            out << '\n';
    }
}

#endif