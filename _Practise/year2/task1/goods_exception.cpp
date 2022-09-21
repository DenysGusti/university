#include "goods_exception.h"

GoodsException::GoodsException(string_view msg) : message{msg} {}

const char *GoodsException::what() const noexcept {
    return message.c_str();
}
