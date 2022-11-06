#ifndef UNIVERSITY_CONSOLE_LOGGER_HPP
#define UNIVERSITY_CONSOLE_LOGGER_HPP

#include "logger.hpp"

class ConsoleLogger : public Logger {
public:
    void logError() const noexcept override;

    void logInfo() const noexcept override;

    void logWarning() const noexcept override;
};

void ConsoleLogger::logError() const noexcept {
    cout << "Log Error: Some error text." << endl;
}

void ConsoleLogger::logInfo() const noexcept {
    cout << "Log Info: Some info text." << endl;
}

void ConsoleLogger::logWarning() const noexcept {
    cout << "Log Warning: Some warning text." << endl;
}

#endif
