#ifndef UNIVERSITY_MENU_EXCEPTION_H
#define UNIVERSITY_MENU_EXCEPTION_H

#include <string>

using namespace std;

class MenuException : private exception {
    string message;

public:
    explicit MenuException(string_view msg);

    const char *what() const noexcept override;
};

#endif
