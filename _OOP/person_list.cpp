#include <iostream>
#include <list>
#include <algorithm>
#include <random>

using namespace std;

class Person {
private:
    string name;
    uint64_t age{};

public:
    Person(string_view name_, const uint64_t age_) : name{name_}, age{age_} {}

    string getName() const noexcept {
        return name;
    }

    uint64_t getAge() const noexcept {
        return age;
    }
};


int main() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> age(12, 24);

    list<Person> persons = {{"Artem",   age(gen)},
                            {"Julia",   age(gen)},
                            {"Andrii",  age(gen)},
                            {"Denys",   age(gen)},
                            {"Vlad",    age(gen)},
                            {"Sofia",   age(gen)},
                            {"Olexii",  age(gen)},
                            {"Ivan",    age(gen)},
                            {"Bozhena", age(gen)},
                            {"Nazar",   age(gen)}};

    for (const auto &el: persons)
        cout << el.getName() << ' ' << el.getAge() << '\n';

    erase_if(persons, [](const auto &person) -> bool { return person.getAge() < 18; });

    for (cout << '\n'; const auto &el: persons)
        cout << el.getName() << ' ' << el.getAge() << '\n';
    return 0;
}