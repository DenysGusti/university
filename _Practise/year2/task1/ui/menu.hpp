#ifndef UNIVERSITY_MENU_H
#define UNIVERSITY_MENU_H

#include <iostream>
#include <functional>
#include <format>
#include <string>

#include "../exceptions/menu_exception.hpp"
#include "../exceptions/option_exception.hpp"
#include "../logistics/shipping_list.hpp"

using namespace std;

class Menu {
private:
    shared_ptr<ShippingList> pShippingList;

    enum class Option : uint8_t {
        Zero, First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth, Tenth, Eleventh, Twelve, Thirteen
    };

    template<class... Args>
    static auto functionWrapper(const auto &func, Args &&... args);

    static int getInput();

    static Option getOption();

    void baseMenu();

    void shippingMenu();

    void sortShippingMenu();

    void dataMenu(string_view dataType);

public:
    explicit Menu(const shared_ptr<ShippingList> &d);
};

template<class... Args>
auto Menu::functionWrapper(const auto &func, Args &&... args) {
    while (true)
        try {
            return func(args...);

        } catch (const MenuException &e) {
            cerr << e.what() << endl;
            cout << "Choose valid menu option!" << endl;

        } catch (const OptionException &e) {
            cerr << e.what() << endl;
            cout << "Enter valid number for option!" << endl;

        } catch (const invalid_argument &e) {
            cerr << e.what() << endl;
            cout << "Enter a number!" << endl;

        } catch (const out_of_range &e) {
            cerr << e.what() << endl;
            cout << "Don't pop from empty array!" << endl;
        }
}

Menu::Menu(const shared_ptr<ShippingList> &d) : pShippingList{d} {
    functionWrapper([&] { baseMenu(); });
}

int Menu::getInput() {
    string input;
    cin >> input;
    return stoi(input);
}

Menu::Option Menu::getOption() {
    switch (functionWrapper(getInput)) {
        case 0:
            return Option::Zero;

        case 1:
            return Option::First;

        case 2:
            return Option::Second;

        case 3:
            return Option::Third;

        case 4:
            return Option::Fourth;

        case 5:
            return Option::Fifth;

        case 6:
            return Option::Sixth;

        case 7:
            return Option::Seventh;

        case 8:
            return Option::Eighth;

        case 9:
            return Option::Ninth;

        case 10:
            return Option::Tenth;

        case 11:
            return Option::Eleventh;

        case 12:
            return Option::Twelve;

        case 13:
            return Option::Thirteen;

        default:
            throw OptionException("Invalid number for option!");
    }
}

void Menu::baseMenu() {
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

void Menu::shippingMenu() {
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
                break;

            case Option::Second:
                pShippingList->addNewFromFile();
                break;

            case Option::Third:
                pShippingList->deleteFirst();
                break;

            case Option::Fourth:
                pShippingList->deleteLast();
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

void Menu::sortShippingMenu() {
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
                break;

            case Option::Second:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getGoods().getName() < b->getGoods().getName(); });
                break;

            case Option::Third:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getGoods().getQuantity() < b->getGoods().getQuantity(); });
                break;

            case Option::Fourth:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getWarehouseFrom().getName() < b->getWarehouseFrom().getName(); });
                break;

            case Option::Fifth:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getWarehouseFrom().getCity() < b->getWarehouseFrom().getCity(); });
                break;

            case Option::Sixth:
                pShippingList->sortAll(
                        [](el a, el b) {
                            return a->getWarehouseFrom().getCapacity() < b->getWarehouseFrom().getCapacity();
                        });
                break;

            case Option::Seventh:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getWarehouseTo().getName() < b->getWarehouseTo().getName(); });
                break;

            case Option::Eighth:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getWarehouseTo().getCity() < b->getWarehouseTo().getCity(); });
                break;

            case Option::Ninth:
                pShippingList->sortAll([](el a, el b) {
                    return a->getWarehouseTo().getCapacity() < b->getWarehouseTo().getCapacity();
                });
                break;

            case Option::Tenth:
                pShippingList->sortAll([](el a, el b) { return a->getDriver().getName() < b->getDriver().getName(); });
                break;

            case Option::Eleventh:
                pShippingList->sortAll(
                        [](el a, el b) { return a->getDriver().getSurname() < b->getDriver().getSurname(); });
                break;

            case Option::Twelve:
                pShippingList->sortAll([](el a, el b) { return a->getDriver().getAge() < b->getDriver().getAge(); });
                break;

            case Option::Thirteen:
                pShippingList->sortAll([](el a, el b) { return a->getDuration() < b->getDuration(); });
                break;


            default:
                throw MenuException("Invalid menu option!");
        }
    }
}

void Menu::dataMenu(string_view dataType) {
    while (true) {
        cout << "Select an option:\n"
             << "0. Back.\n"
             << format("1. Print all {} to terminal in direct order.\n", dataType)
             << format("2. Print all {} to terminal in reverse order.\n", dataType)
             << format("3. Print all {} to file in direct order.\n", dataType)
             << format("4. Print all {} to file in reverse order.\n", dataType) << endl;

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

#endif
