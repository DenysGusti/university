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
                 << "1. Print all shippings in direct order to terminal.\n"
                 << "2. Print all shippings in reverse order to terminal.\n"
                 << "3. Print all shippings in direct order to file.\n"
                 << "4. Print all shippings in reverse order to file." << endl;

            switch (functionWrapper(getOption)) {
                case Option::Zero:
                    return;

                case Option::First:
                    pShippingList->printAllToTerminal(false);
                    break;

                case Option::Second:
                    pShippingList->printAllToTerminal(true);
                    break;

                case Option::Third:
                    pShippingList->printAllToFile(false);
                    break;

                case Option::Fourth:
                    pShippingList->printAllToFile(true);
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
