#include "flotilla.h"

Flotilla::Flotilla(const char *company_name_) {
    strcpy_s(company_name, company_name_);
}

Flotilla &Flotilla::operator+=(const Plane &plane) {
    planes[size++] = plane;
    return *this;
}

void Flotilla::addNewPlane() {
    Plane plane;
    cin >> plane;
    *this += plane;
}

ostream &operator<<(ostream &os, const Flotilla &obj) {
    os << obj.company_name << '\n';

    for (size_t i = 0; i < obj.size; ++i)
        os << obj.planes[i] << '\n';
    return os;
}

istream &operator>>(istream &is, Flotilla &obj) {
    char tmp[100]{};
    if (&is == &cin)
        cout << "Enter company name: ";
    is >> tmp;
    strcpy_s(obj.company_name, tmp);

    if (&is == &cin)
        cout << "Enter number of planes: ";
    is >> obj.size;

    for (size_t i = 0; i < obj.size; ++i)
        cin >> obj.planes[i];
    return is;
}

size_t Flotilla::countAutopilot() {
    size_t c = 0;
    for (size_t i = 0; i < size; ++i)
        if (planes[i].hasAutopilot())
            ++c;
    return c;
}

void Flotilla::printToFile() const {
    ofstream fout{R"(C:\Users\denys\CLionProjects\University\university\_OOP\cw1\out.txt)"};
    fout << *this;
}