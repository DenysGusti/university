#ifndef UNIVERSITY_FLOTILLA_MANAGER_H
#define UNIVERSITY_FLOTILLA_MANAGER_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "flotilla.h"

using namespace std;

class FlotillasManager {
private:
    Flotilla flotillas[10];
    size_t size{};

public:
    FlotillasManager &operator+=(const Flotilla &flotilla);

    void addNewFlotilla();

    Flotilla &operator[](const size_t idx);

    size_t findFlotillaWithMaxAutopilot();
};

#endif
