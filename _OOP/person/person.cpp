#include "person.h"
#include "date.h"

int main() {
    try {
        Person person("a", "b", {1, 9, 2020});
        person.WriteToConsole();
        cout << "Age: " << person.getAge() << '\n';
    } catch (const invalid_argument &exc) {
        cerr << exc.what() << '\n';
    }

}