#ifndef TASK1_5_BASE_STATE_HPP
#define TASK1_5_BASE_STATE_HPP

#include "menu_and_state.hpp"

class BaseMenuState : public State {
private:
    static void showInfo() noexcept;

public:
    BaseMenuState();

    void Handle0() final;

    void Handle1() override = 0;

    void Handle2() override = 0;

    void Handle3() override = 0;

    void Handle4() override = 0;

    void Handle5() override = 0;
};

BaseMenuState::BaseMenuState() {
    showInfo();
}

void BaseMenuState::showInfo() noexcept {
    cout << "Select an option:\n"
         << "0. Exit.\n"
         << "1. Interact with shippings.\n"
         << "2. Interact with goods.\n"
         << "3. Interact with departure warehouses.\n"
         << "4. Interact with destination warehouses.\n"
         << "5. Interact with drivers." << endl;
}

void BaseMenuState::Handle0() {
    menu_->TransitionTo(make_unique<ExitState>());
}

#endif
