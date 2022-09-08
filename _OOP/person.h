#ifndef UNIVERSITY_PERSON_H
#define UNIVERSITY_PERSON_H

#include <string>

using namespace std;

class Person {
    string firstName{}, lastName{};
    int age{};

public:
    Person(string_view fn, string_view ln, const int a) : firstName{fn}, lastName{ln}, age{a} {}

    void WriteToConsole() const {
        cout << firstName << ' ' << lastName << ' ' << age << '\n';
    }

    static int maxAge() {
        return 120;
    }
};

#endif
