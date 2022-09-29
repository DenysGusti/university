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

void
ShippingList::getDataFromFile(string &goodsName, string &driverName, string &driverSurname, string &warehouseFromName,
                              string &warehouseFromCity, string &warehouseToName, string &warehouseToCity, ld &quantity,
                              ld &capacityFrom, ld &capacityTo, uint64_t &duration, uint64_t &age, istream &in) {
    in >> goodsName >> quantity >> warehouseFromName >> warehouseFromCity >> capacityFrom >>
       warehouseToName >> warehouseToCity >> capacityTo >> driverName >> driverSurname >> age >> duration;
}

void ShippingList::getDataFromTerminal(string &goodsName, string &driverName, string &driverSurname,
                                       string &warehouseFromName,
                                       string &warehouseFromCity, string &warehouseToName, string &warehouseToCity,
                                       ld &quantity, ld &capacityFrom, ld &capacityTo, uint64_t &duration,
                                       uint64_t &age) {
    cout << "Enter goods name and quantity, t:" << endl;
    cin >> goodsName >> quantity;

    cout << "Enter departure warehouse name, city and capacity, t:" << endl;
    cin >> warehouseFromName >> warehouseFromCity >> capacityFrom;

    cout << "Enter destination warehouse name, city and capacity, t:" << endl;
    cin >> warehouseToName >> warehouseToCity >> capacityTo;

    cout << "Enter driver's name, surname, age:" << endl;
    cin >> driverName >> driverSurname >> age;

    cout << "Enter duration, days:" << endl;
    cin >> duration;
}

Shipping ShippingList::getShipping(istream &in) {
    string goodsName, driverName, driverSurname, warehouseFromName, warehouseFromCity, warehouseToName, warehouseToCity;
    ld quantity{}, capacityFrom{}, capacityTo{};
    uint64_t duration{}, age{};

    if (&in == &cin)
        getDataFromTerminal(goodsName, driverName, driverSurname, warehouseFromName, warehouseFromCity, warehouseToName,
                            warehouseToCity, quantity, capacityFrom, capacityTo, duration, age);
    else
        getDataFromFile(goodsName, driverName, driverSurname, warehouseFromName, warehouseFromCity, warehouseToName,
                        warehouseToCity, quantity, capacityFrom, capacityTo, duration, age, in);

    Goods g{goodsName, quantity};
    Warehouse wf{warehouseFromName, warehouseFromCity, capacityFrom}, wt{warehouseToName, warehouseToCity, capacityTo};
    Driver d{driverName, driverSurname, age};
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
