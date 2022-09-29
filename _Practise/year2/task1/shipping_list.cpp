#include "shipping_list.h"

ShippingList::ShippingList(string_view in, string_view out) : in_file{in}, out_file{out} {}

void ShippingList::deleteFirstShipping() {
    if (shippings.empty())
        throw out_of_range("Trying to delete element from empty shipping array!");

    shippings.pop_front();
}

void ShippingList::deleteLastShipping() {
    if (shippings.empty())
        throw out_of_range("Trying to delete element from empty shipping array!");

    shippings.pop_back();
}

void ShippingList::printAllShippings(ostream &out, const bool reversed) const {
    if (!reversed)
        for (const auto &pShipping: shippings)
            out << *pShipping << '\n';

    else
        for (const auto &pShipping: shippings | rv::reverse)
            out << *pShipping << '\n';

    out << '\n';
}

void ShippingList::printAllShippingsToTerminal(const bool reversed) const {
    printAllShippings(cout, reversed);
}

void ShippingList::printAllShippingsToFile(const bool reversed = false) const {
    ofstream fout{out_file, ios::app};
    printAllShippings(fout, reversed);
}

Shipping ShippingList::getShipping(istream &in) {
    uint64_t duration{};
    Goods g;
    Warehouse wf, wt;
    Driver d;

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

    return {shippings.size() + 1, duration, g, wf, wt, d};
}

void ShippingList::addNewShippingFromTerminal() {
    shippings.push_back(make_unique<Shipping>(getShipping(cin)));
}

void ShippingList::addNewShippingFromFile() {
    for (ifstream fin{in_file}; !fin.eof(); shippings.push_back(make_unique<Shipping>(getShipping(fin))));
}

void
ShippingList::sortAllShippings(const function<bool(const unique_ptr<Shipping> &, const unique_ptr<Shipping> &)> &func) {
    ranges::sort(shippings, func);
}

void ShippingList::printOnlyToTerminal(string_view dataType, bool reversed) const {
    printOnly(dataType, cout, reversed);
}

void ShippingList::printOnlyToFile(string_view dataType, bool reversed) const {
    ofstream fout{out_file, ios::app};
    printOnly(dataType, fout, reversed);
}

void ShippingList::printOnly(string_view dataType, ostream &out, bool reversed) const {
    if (!reversed)
        for (const auto &pShipping: shippings) {
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
        for (const auto &pShipping: shippings | rv::reverse) {
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
    return shippings.size();
}

ShippingList &ShippingList::operator+=(const Shipping &newShipping) {
    shippings.push_back(make_unique<Shipping>(newShipping));
    return *this;
}
