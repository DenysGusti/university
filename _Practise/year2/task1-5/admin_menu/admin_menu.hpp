#ifndef ADMIN_MENU_ADMIN_MENU_HPP
#define ADMIN_MENU_ADMIN_MENU_HPP

#include "../menu.hpp"

class AdminMenu : public Menu {
public:
    explicit AdminMenu(const shared_ptr<ShippingList> &d) : Menu{d} {
        functionWrapper([&] { baseMenu(); });
    }

    void baseMenu() override {
        pShippingList->addNewFromFile();

        while (true) {
            cout << "Select an option:\n"
                 << "0. Exit.\n"
                 << "1. Interact with shippings.\n"
                 << "2. Interact with goods.\n"
                 << "3. Interact with departure warehouses.\n"
                 << "4. Interact with destination warehouses.\n"
                 << "5. Interact with drivers." << endl;

            switch (functionWrapper(getOption)) {
                case Option::Zero:
                    return;

                case Option::First:
                    functionWrapper([&] { shippingMenu(); });
                    break;

                case Option::Second:
                    functionWrapper([&] { dataMenu("goods"); });
                    break;

                case Option::Third:
                    functionWrapper([&] { dataMenu("departure warehouses"); });
                    break;

                case Option::Fourth:
                    functionWrapper([&] { dataMenu("destination warehouses"); });
                    break;

                case Option::Fifth:
                    functionWrapper([&] { dataMenu("drivers"); });
                    break;

                default:
                    throw MenuException("Invalid menu option!");
            }
        }
    }

    void shippingMenu() override {
        pShippingList->addNewFromFile();

        while (true) {
            cout << "Select an option:\n"
                 << "0. Back.\n"
                 << "1. Add new shipping from terminal.\n"
                 << "2. Add shippings from the file.\n"
                 << "3. Delete first shipping.\n"
                 << "4. Delete last shipping.\n"
                 << "5. Print all shippings in direct order to terminal.\n"
                 << "6. Print all shippings in reverse order to terminal.\n"
                 << "7. Print all shippings in direct order to file.\n"
                 << "8. Print all shippings in reverse order to file.\n"
                 << "9. Sort all shippings." << endl;

            switch (functionWrapper(getOption)) {
                case Option::Zero:
                    return;

                case Option::First:
                    pShippingList->addNewFromTerminal();
                    pShippingList->updateFile();
                    break;

                case Option::Second:
                    pShippingList->addNewFromFile();
                    pShippingList->updateFile();
                    break;

                case Option::Third:
                    pShippingList->deleteFirst();
                    pShippingList->updateFile();
                    break;

                case Option::Fourth:
                    pShippingList->deleteLast();
                    pShippingList->updateFile();
                    break;

                case Option::Fifth:
                    pShippingList->printAllToTerminal(false);
                    break;

                case Option::Sixth:
                    pShippingList->printAllToTerminal(true);
                    break;

                case Option::Seventh:
                    pShippingList->printAllToFile(false);
                    break;

                case Option::Eighth:
                    pShippingList->printAllToFile(true);
                    break;

                case Option::Ninth:
                    functionWrapper([&] { sortShippingMenu(); });
                    break;

                default:
                    throw MenuException("Invalid menu option!");
            }
        }
    }

    void sortShippingMenu() {
        pShippingList->addNewFromFile();

        using el = const unique_ptr<Shipping> &;
        while (true) {
            cout << "Select an option:\n"
                 << "0. Back.\n"
                 << "1. Sort by order.\n"
                 << "2. Sort by goods name.\n"
                 << "3. Sort by goods quantity.\n"
                 << "4. Sort by departure warehouse name.\n"
                 << "5. Sort by departure warehouse city.\n"
                 << "6. Sort by departure warehouse capacity.\n"
                 << "7. Sort by destination warehouse name.\n"
                 << "8. Sort by destination warehouse city.\n"
                 << "9. Sort by destination warehouse capacity.\n"
                 << "10. Sort by driver's name.\n"
                 << "11. Sort by driver's surname.\n"
                 << "12. Sort by driver's age.\n"
                 << "13. Sort by duration." << endl;

            switch (functionWrapper(getOption)) {
                case Option::Zero:
                    return;

                case Option::First:
                    pShippingList->sortAll([](el a, el &b) { return a->getOrder() < b->getOrder(); });
                    pShippingList->updateFile();
                    break;

                case Option::Second:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getGoods().getName() < b->getGoods().getName(); });
                    pShippingList->updateFile();
                    break;

                case Option::Third:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getGoods().getQuantity() < b->getGoods().getQuantity(); });
                    pShippingList->updateFile();
                    break;

                case Option::Fourth:
                    pShippingList->sortAll(
                            [](el a, el b) {
                                return a->getWarehouseFrom().getName() < b->getWarehouseFrom().getName();
                            });
                    pShippingList->updateFile();
                    break;

                case Option::Fifth:
                    pShippingList->sortAll(
                            [](el a, el b) {
                                return a->getWarehouseFrom().getCity() < b->getWarehouseFrom().getCity();
                            });
                    pShippingList->updateFile();
                    break;

                case Option::Sixth:
                    pShippingList->sortAll(
                            [](el a, el b) {
                                return a->getWarehouseFrom().getCapacity() < b->getWarehouseFrom().getCapacity();
                            });
                    pShippingList->updateFile();
                    break;

                case Option::Seventh:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getWarehouseTo().getName() < b->getWarehouseTo().getName(); });
                    pShippingList->updateFile();
                    break;

                case Option::Eighth:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getWarehouseTo().getCity() < b->getWarehouseTo().getCity(); });
                    pShippingList->updateFile();
                    break;

                case Option::Ninth:
                    pShippingList->sortAll([](el a, el b) {
                        return a->getWarehouseTo().getCapacity() < b->getWarehouseTo().getCapacity();
                    });
                    pShippingList->updateFile();
                    break;

                case Option::Tenth:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getDriver().getName() < b->getDriver().getName(); });
                    pShippingList->updateFile();
                    break;

                case Option::Eleventh:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getDriver().getSurname() < b->getDriver().getSurname(); });
                    pShippingList->updateFile();
                    break;

                case Option::Twelve:
                    pShippingList->sortAll(
                            [](el a, el b) { return a->getDriver().getAge() < b->getDriver().getAge(); });
                    pShippingList->updateFile();
                    break;

                case Option::Thirteen:
                    pShippingList->sortAll([](el a, el b) { return a->getDuration() < b->getDuration(); });
                    pShippingList->updateFile();
                    break;

                default:
                    throw MenuException("Invalid menu option!");
            }
        }
    }

    void dataMenu(string_view dataType) override {
        pShippingList->addNewFromFile();

        while (true) {
            cout << "Select an option:\n"
                 << "0. Back.\n"
                 << format("1. Print all {} to terminal in direct order.\n", dataType)
                 << format("2. Print all {} to terminal in reverse order.\n", dataType)
                 << format("3. Print all {} to file in direct order.\n", dataType)
                 << format("4. Print all {} to file in reverse order.", dataType) << endl;

            switch (functionWrapper(getOption)) {
                case Option::Zero:
                    return;

                case Option::First:
                    pShippingList->printOnlyToTerminal(dataType, false);
                    break;

                case Option::Second:
                    pShippingList->printOnlyToTerminal(dataType, true);
                    break;

                case Option::Third:
                    pShippingList->printOnlyToFile(dataType, false);
                    break;

                case Option::Fourth:
                    pShippingList->printOnlyToFile(dataType, true);
                    break;

                default:
                    throw MenuException("Invalid menu option!");
            }
        }
    }
};

#endif
