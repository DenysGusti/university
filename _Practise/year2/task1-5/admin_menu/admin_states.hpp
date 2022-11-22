#ifndef TASK1_5_ADMIN_STATES_HPP
#define TASK1_5_ADMIN_STATES_HPP

#include "../menu_and_state.hpp"
#include "../data_state.hpp"
#include "../base_state.hpp"

class StateBaseMenuAdmin : public BaseMenuState {
public:
    void Handle1() override;

    void Handle2() override;

    void Handle3() override;

    void Handle4() override;

    void Handle5() override;
};


class StateShippingMenuAdmin : public State {
private:
    static void showInfo() noexcept;

public:
    StateShippingMenuAdmin();

    void Handle0() override;

    void Handle1() override;

    void Handle2() override;

    void Handle3() override;

    void Handle4() override;

    void Handle5() override;

    void Handle6() override;

    void Handle7() override;

    void Handle8() override;

    void Handle9() override;
};

class DataStateAdmin : public DataState {
public:
    explicit DataStateAdmin(string_view dataType);

    void Handle0() override;
};

class StateSortShippingMenu : public State {
private:
    using el = const unique_ptr<Shipping> &;

    static void showInfo() noexcept;

public:
    StateSortShippingMenu();

    void Handle0() override;

    void Handle1() override;

    void Handle2() override;

    void Handle3() override;

    void Handle4() override;

    void Handle5() override;

    void Handle6() override;

    void Handle7() override;

    void Handle8() override;

    void Handle9() override;

    void Handle10() override;

    void Handle11() override;

    void Handle12() override;

    void Handle13() override;
};

void StateBaseMenuAdmin::Handle1() {
    menu_->TransitionTo(make_unique<StateShippingMenuAdmin>());
}

void StateBaseMenuAdmin::Handle2() {
    menu_->TransitionTo(make_unique<DataStateAdmin>("goods"));
}

void StateBaseMenuAdmin::Handle3() {
    menu_->TransitionTo(make_unique<DataStateAdmin>("departure warehouses"));
}

void StateBaseMenuAdmin::Handle4() {
    menu_->TransitionTo(make_unique<DataStateAdmin>("destination warehouses"));
}

void StateBaseMenuAdmin::Handle5() {
    menu_->TransitionTo(make_unique<DataStateAdmin>("drivers"));
}

StateShippingMenuAdmin::StateShippingMenuAdmin() {
    showInfo();
}

void StateShippingMenuAdmin::showInfo() noexcept {
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
}


void StateShippingMenuAdmin::Handle0() {
    menu_->TransitionTo(make_unique<StateBaseMenuAdmin>());
}

void StateShippingMenuAdmin::Handle1() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->addNewFromTerminal();
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateShippingMenuAdmin::Handle2() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateShippingMenuAdmin::Handle3() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->deleteFirst();
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateShippingMenuAdmin::Handle4() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->deleteLast();
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateShippingMenuAdmin::Handle5() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToTerminal(false);
    showInfo();
}

void StateShippingMenuAdmin::Handle6() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToTerminal(true);
    showInfo();
}

void StateShippingMenuAdmin::Handle7() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToFile(false);
    showInfo();
}

void StateShippingMenuAdmin::Handle8() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->printAllToFile(true);
    showInfo();
}

void StateShippingMenuAdmin::Handle9() {
    menu_->TransitionTo(make_unique<StateSortShippingMenu>());
}

DataStateAdmin::DataStateAdmin(string_view dataType) : DataState(dataType) {}


void DataStateAdmin::Handle0() {
    menu_->TransitionTo(make_unique<StateBaseMenuAdmin>());
}

StateSortShippingMenu::StateSortShippingMenu() {
    showInfo();
}

void StateSortShippingMenu::showInfo() noexcept {
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
}

void StateSortShippingMenu::Handle0() {
    menu_->TransitionTo(make_unique<StateShippingMenuAdmin>());
}

void StateSortShippingMenu::Handle1() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll([](el a, el &b) { return a->getOrder() < b->getOrder(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle2() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getGoods().getName() < b->getGoods().getName(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle3() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getGoods().getQuantity() < b->getGoods().getQuantity(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle4() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getWarehouseFrom().getName() < b->getWarehouseFrom().getName(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle5() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getWarehouseFrom().getCity() < b->getWarehouseFrom().getCity(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle6() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getWarehouseFrom().getCapacity() < b->getWarehouseFrom().getCapacity(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle7() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getWarehouseTo().getName() < b->getWarehouseTo().getName(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle8() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getWarehouseTo().getCity() < b->getWarehouseTo().getCity(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle9() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll([](el a, el b) {
        return a->getWarehouseTo().getCapacity() < b->getWarehouseTo().getCapacity();
    });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle10() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getDriver().getName() < b->getDriver().getName(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle11() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getDriver().getSurname() < b->getDriver().getSurname(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle12() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll(
            [](el a, el b) { return a->getDriver().getAge() < b->getDriver().getAge(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

void StateSortShippingMenu::Handle13() {
    menu_->pShippingList->addNewFromFile();
    menu_->pShippingList->sortAll([](el a, el b) { return a->getDuration() < b->getDuration(); });
    menu_->pShippingList->updateFile();
    showInfo();
}

#endif
