#include "logger_factory.hpp"

LoggerFactory *getFactory() {
    char option{};
    cout << "Write 1 for console logger or 2 for file logger: " << endl;
    cin >> option;

    if (option == '1')
        return new ConsoleLoggerFactory;

    if (option == '2')
        return new FileLoggerFactory;

    cout << "Wrong option!" << endl;
    return nullptr;
}

int main() {
    LoggerFactory *factory{};
    Logger *logger{};

    char cont{};
    do {
        factory = getFactory();
        if (factory) {
            logger = factory->createLogger();
            logger->logError();
            logger->logInfo();
            logger->logWarning();
        }
        cout << "Continue? y/n" << endl;
        cin >> cont;
    } while (cont == 'y');

    delete factory;
    delete logger;
    return 0;
}