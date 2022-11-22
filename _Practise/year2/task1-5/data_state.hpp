#ifndef TASK1_5_DATA_STATE_HPP
#define TASK1_5_DATA_STATE_HPP

#include "menu_and_state.hpp"

class DataState : public State {
private:
    string _dataType;

    void showInfo() const noexcept;

public:
    explicit DataState(string_view dataType);

    void Handle0() override = 0;

    void Handle1() final;

    void Handle2() final;

    void Handle3() final;

    void Handle4() final;
};

DataState::DataState(string_view dataType) : _dataType{dataType} {
    showInfo();
}

void DataState::showInfo() const noexcept {
    cout << "Select an option:\n"
         << "0. Back.\n"
         << format("1. Print all {} to terminal in direct order.\n", _dataType)
         << format("2. Print all {} to terminal in reverse order.\n", _dataType)
         << format("3. Print all {} to file in direct order.\n", _dataType)
         << format("4. Print all {} to file in reverse order.", _dataType) << endl;
}

void DataState::Handle1() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printOnlyToTerminal(_dataType, false);
    showInfo();
}

void DataState::Handle2() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printOnlyToTerminal(_dataType, true);
    showInfo();
}

void DataState::Handle3() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printOnlyToFile(_dataType, false);
    showInfo();
}

void DataState::Handle4() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printOnlyToFile(_dataType, true);
    showInfo();
}

#endif
