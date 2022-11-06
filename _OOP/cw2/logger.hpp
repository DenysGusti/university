#ifndef UNIVERSITY_LOGGER_HPP
#define UNIVERSITY_LOGGER_HPP

#include <iostream>
#include <fstream>

using namespace std;

class Logger {
public:
    virtual ~Logger() = default;

    virtual void logError() const noexcept = 0;

    virtual void logInfo() const noexcept = 0;

    virtual void logWarning() const noexcept = 0;
};

#endif
