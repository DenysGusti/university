#ifndef TASK1_5_FUNCTIONS_HPP
#define TASK1_5_FUNCTIONS_HPP

#include <iostream>

#include "shipping_logic/exceptions/menu_exception.hpp"
#include "shipping_logic/exceptions/option_exception.hpp"
#include "shipping_logic/logistics/shipping_list.hpp"

#include "menu_and_state.hpp"

using namespace std;

template<class... Args>
auto functionWrapper(const auto &func, Args &&... args) {
    while (true)
        try {
            return func(std::forward<Args &&...>(args...));
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

int64_t getInput() {
    string input;
    cin >> input;
    return stoll(input);
}

enum class Option : uint8_t {
    Zero, First, Second, Third, Fourth, Fifth, Sixth, Seventh, Eighth, Ninth, Tenth, Eleventh, Twelve, Thirteen
};

Option getOption() {
    switch (getInput()) {
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

void inputHandle(Menu &&menu) {
    while (true)
        switch (getOption()) {
            case Option::Zero:
                menu.Request0();
                if (menu.hasExitState())
                    return;
                break;
            case Option::First:
                menu.Request1();
                break;
            case Option::Second:
                menu.Request2();
                break;
            case Option::Third:
                menu.Request3();
                break;
            case Option::Fourth:
                menu.Request4();
                break;
            case Option::Fifth:
                menu.Request5();
                break;
            case Option::Sixth:
                menu.Request6();
                break;
            case Option::Seventh:
                menu.Request7();
                break;
            case Option::Eighth:
                menu.Request8();
                break;
            case Option::Ninth:
                menu.Request9();
                break;
            case Option::Tenth:
                menu.Request10();
                break;
            case Option::Eleventh:
                menu.Request11();
                break;
            case Option::Twelve:
                menu.Request12();
                break;
            case Option::Thirteen:
                menu.Request13();
                break;
            default:
                throw MenuException("Invalid menu option!");
        }
}

#endif
