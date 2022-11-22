#ifndef TASK1_5_USER_STATES_HPP
#define TASK1_5_USER_STATES_HPP

#include "../menu_and_state.hpp"
#include "../data_state.hpp"
#include "../base_state.hpp"

class StateBaseMenuUser : public BaseMenuState {
public:
    void Handle1() override;

    void Handle2() override;

    void Handle3() override;

    void Handle4() override;

    void Handle5() override;
};


class StateShippingMenuUser : public State {
private:
    static void showInfo() noexcept;

public:
    StateShippingMenuUser();

    void Handle0() override;

    void Handle1() override;

    void Handle2() override;

    void Handle3() override;

    void Handle4() override;
};

class DataStateUser : public DataState {
public:
    explicit DataStateUser(string_view dataType);

    void Handle0() override;
};

void StateBaseMenuUser::Handle1() {
    menu_->TransitionTo(make_unique<StateShippingMenuUser>());
}

void StateBaseMenuUser::Handle2() {
    menu_->TransitionTo(make_unique<DataStateUser>("goods"));
}

void StateBaseMenuUser::Handle3() {
    menu_->TransitionTo(make_unique<DataStateUser>("departure warehouses"));
}

void StateBaseMenuUser::Handle4() {
    menu_->TransitionTo(make_unique<DataStateUser>("destination warehouses"));
}

void StateBaseMenuUser::Handle5() {
    menu_->TransitionTo(make_unique<DataStateUser>("drivers"));
}

StateShippingMenuUser::StateShippingMenuUser() {
    showInfo();
}


void StateShippingMenuUser::showInfo() noexcept {
    cout << "Select an option:\n"
         << "0. Back.\n"
         << "1. Print all shippings in direct order to terminal.\n"
         << "2. Print all shippings in reverse order to terminal.\n"
         << "3. Print all shippings in direct order to file.\n"
         << "4. Print all shippings in reverse order to file." << endl;
}

void StateShippingMenuUser::Handle0() {
    menu_->TransitionTo(make_unique<StateBaseMenuUser>());
}

void StateShippingMenuUser::Handle1() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToTerminal(false);
    showInfo();
}

void StateShippingMenuUser::Handle2() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToTerminal(true);
    showInfo();
}

void StateShippingMenuUser::Handle3() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToFile(false);
    showInfo();
}

void StateShippingMenuUser::Handle4() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToFile(true);
    showInfo();
}


DataStateUser::DataStateUser(string_view dataType) : DataState(dataType) {}

void DataStateUser::Handle0() {
    menu_->TransitionTo(make_unique<StateBaseMenuUser>());
}

#endif
