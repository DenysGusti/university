#ifndef UNIVERSITY_MENU_H
#define UNIVERSITY_MENU_H

#include <iostream>
#include <functional>
#include <format>
#include <string>

#include "menu_exception.h"
#include "option_exception.h"
#include "shipping_list.h"

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

#endif
