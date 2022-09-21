#include "menu_exception.h"

MenuException::MenuException(string_view msg) : message{msg} {}

const char *MenuException::what() const noexcept {
    return message.c_str();
}
