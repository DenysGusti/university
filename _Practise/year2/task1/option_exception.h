#ifndef UNIVERSITY_OPTION_EXCEPTION_H
#define UNIVERSITY_OPTION_EXCEPTION_H

#include <string>

using namespace std;

class OptionException : private exception {
    string message;

public:
    explicit OptionException(string_view msg);

    const char *what() const noexcept override;
};

#endif
