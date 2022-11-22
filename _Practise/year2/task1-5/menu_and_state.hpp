#ifndef TASK1_5_MENU_AND_STATE_HPP
#define TASK1_5_MENU_AND_STATE_HPP

#include <iostream>
#include <typeinfo>
#include <memory>
#include <functional>
#include <format>
#include <string>

#include "shipping_logic/exceptions/menu_exception.hpp"
#include "shipping_logic/exceptions/option_exception.hpp"
#include "shipping_logic/logistics/shipping_list.hpp"

using namespace std;

class Menu;

class State {
protected:
    Menu *menu_{};

public:
    [[nodiscard]] virtual bool isExitState() const noexcept {
        return false;
    }

    virtual ~State() = default;

    void set_Menu(Menu *menu) {
        menu_ = menu;
    }

    virtual void Handle0() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle1() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle2() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle3() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle4() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle5() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle6() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle7() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle8() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle9() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle10() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle11() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle12() {
        throw MenuException("Invalid menu option!");
    };

    virtual void Handle13() {
        throw MenuException("Invalid menu option!");
    };
};

class Menu {
private:
    unique_ptr<State> state_;
    unique_ptr<ShippingList> pShippingList;

    friend class DataState;

    friend class StateBaseMenuUser;

    friend class StateBaseMenuAdmin;

    friend class StateShippingMenuUser;

    friend class StateShippingMenuAdmin;

    friend class StateSortShippingMenu;

public:
    explicit Menu(unique_ptr<State> state, unique_ptr<ShippingList> pSl) : pShippingList{std::move(pSl)} {
        TransitionTo(std::move(state));
    }

    void TransitionTo(unique_ptr<State> state) {
        state_ = std::move(state);
        state_->set_Menu(this);
    }

    [[nodiscard]] bool hasExitState() const noexcept {
        return state_->isExitState();
    }

    void Request0() {
        state_->Handle0();
    }

    void Request1() {
        state_->Handle1();
    }

    void Request2() {
        state_->Handle2();
    }

    void Request3() {
        state_->Handle3();
    }

    void Request4() {
        state_->Handle4();
    }

    void Request5() {
        state_->Handle5();
    }

    void Request6() {
        state_->Handle6();
    }

    void Request7() {
        state_->Handle7();
    }

    void Request8() {
        state_->Handle8();
    }

    void Request9() {
        state_->Handle9();
    }

    void Request10() {
        state_->Handle10();
    }

    void Request11() {
        state_->Handle11();
    }

    void Request12() {
        state_->Handle12();
    }

    void Request13() {
        state_->Handle13();
    }
};

class ExitState : public State {
public:
    [[nodiscard]] bool isExitState() const noexcept override {
        return true;
    }
};

#endif
