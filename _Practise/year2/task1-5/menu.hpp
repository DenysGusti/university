#ifndef UNIVERSITY_MENU_H
#define UNIVERSITY_MENU_H

#include <iostream>
#include <functional>
#include <format>
#include <string>

#include "shipping_logic/exceptions/menu_exception.hpp"
#include "shipping_logic/exceptions/option_exception.hpp"
#include "shipping_logic/logistics/shipping_list.hpp"

using namespace std;

template<class... Args>
auto functionWrapper(const auto &func, Args &&... args) {
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

class Menu {
protected:
    shared_ptr<ShippingList> pShippingList;

    enum class Option : uint8_t {
        Zero, First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth, Tenth, Eleventh, Twelve, Thirteen
    };

    static int64_t getInput();

    static Option getOption();

public:
    explicit Menu(const shared_ptr<ShippingList> &d);

    virtual void baseMenu() = 0;

    virtual void shippingMenu() = 0;

    virtual void dataMenu(string_view dataType) = 0;
};


Menu::Menu(const shared_ptr<ShippingList> &d) : pShippingList{d} {}

int64_t Menu::getInput() {
    string input;
    cin >> input;
    return stoll(input);
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

#endif
