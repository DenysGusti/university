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

#endif
