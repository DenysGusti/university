#ifndef UNIVERSITY_FILE_LOGGER_HPP
#define UNIVERSITY_FILE_LOGGER_HPP

#include "logger.hpp"

class FileLogger : public Logger {
public:
    void logError() const noexcept override;

    void logInfo() const noexcept override;

    void logWarning() const noexcept override;
};

void FileLogger::logError() const noexcept {
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_OOP\cw2\log.txt)", ios::app}; // change path!
    fout << "Log Error: Some error text.\n";
}

void FileLogger::logInfo() const noexcept {
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_OOP\cw2\log.txt)", ios::app}; // change path!
    fout << "Log Info: Some info text.\n";
}

void FileLogger::logWarning() const noexcept {
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_OOP\cw2\log.txt)", ios::app}; // change path!
    fout << "Log Warning: Some warning text.\n";
}

#endif
