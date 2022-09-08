#include <iostream>

#include "person.h"

using namespace std;

int main() {
    Person person("a", "b", 18);
    person.WriteToConsole();
    return 0;
}