#include "option_exception.h"

OptionException::OptionException(string_view msg) : message{msg} {}

const char *OptionException::what() const noexcept {
    return message.c_str();
}
