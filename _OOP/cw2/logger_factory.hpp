#ifndef UNIVERSITY_LOGGER_FACTORY_HPP
#define UNIVERSITY_LOGGER_FACTORY_HPP

#include "console_logger.hpp"
#include "file_logger.hpp"

class LoggerFactory {
public:
    virtual ~ LoggerFactory() = default;

    virtual Logger *createLogger() const noexcept = 0;
};

class ConsoleLoggerFactory : public LoggerFactory {
public:
    Logger *createLogger() const noexcept override;
};

class FileLoggerFactory : public LoggerFactory {
public:
    Logger *createLogger() const noexcept override;
};

Logger *ConsoleLoggerFactory::createLogger() const noexcept {
    return new ConsoleLogger;
}

Logger *FileLoggerFactory::createLogger() const noexcept {
    return new FileLogger;
}

#endif
