#ifndef UNIVERSITY_FLOTILLA_H
#define UNIVERSITY_FLOTILLA_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "plane.h"

using namespace std;

class Flotilla {
private:
    char company_name[100]{};
    Plane planes[10]; // too much code for dynamic array reallocation
    size_t size{};

public:
    Flotilla() = default;

    explicit Flotilla(const char *company_name_);

    Flotilla &operator+=(const Plane &plane);

    void addNewPlane();

    friend ostream &operator<<(ostream &os, const Flotilla &obj);

    friend istream &operator>>(istream &is, Flotilla &obj);

    size_t countAutopilot();

    void printToFile() const;
};

#endif
