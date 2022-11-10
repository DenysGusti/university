#ifndef UNIVERSITY_GOODS_EXCEPTION_H
#define UNIVERSITY_GOODS_EXCEPTION_H

#include <string>

using namespace std;

class GoodsException : private exception {
    string message;

public:
    explicit GoodsException(string_view msg);

    const char *what() const noexcept override;
};

GoodsException::GoodsException(string_view msg) : message{msg} {}

const char *GoodsException::what() const noexcept {
    return message.c_str();
}

#endif
