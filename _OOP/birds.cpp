#include <iostream>
#include <array>
#include <memory>
#include <string>
#include <algorithm>
#include <ranges> // c++ 20

using namespace std;

class Bird {
public:
    virtual ~Bird() = default;

    virtual string getName() const noexcept = 0;

    virtual bool compareTo(const Bird &other) const noexcept = 0;
};

class Eagle : public Bird {
private:
    string name;

public:
    explicit Eagle(string_view name_) : name{name_} {}

    string getName() const noexcept override {
        return name;
    }

    bool compareTo(const Bird &other) const noexcept override {
        return name < other.getName();
    }
};

class Swallow : public Bird {
private:
    string name;

public:
    explicit Swallow(string_view name_) : name{name_} {}

    string getName() const noexcept override {
        return name;
    }

    bool compareTo(const Bird &other) const noexcept override {
        return name < other.getName();
    }
};

class Penguin : public Bird {
private:
    string name;

public:
    explicit Penguin(string_view name_) : name{name_} {}

    string getName() const noexcept override {
        return name;
    }

    bool compareTo(const Bird &other) const noexcept override {
        return name < other.getName();
    }
};

class Chicken : public Bird {
private:
    string name;

public:
    explicit Chicken(string_view name_) : name{name_} {}

    string getName() const noexcept override {
        return name;
    }

    bool compareTo(const Bird &other) const noexcept override {
        return name < other.getName();
    }
};

int main() {
    array<unique_ptr<Bird>, 4> birds = {make_unique<Eagle>("Bird E"), make_unique<Swallow>("Bird S"),
                                        make_unique<Penguin>("Bird P"), make_unique<Chicken>("Bird C")};

    ranges::sort(birds, [](const auto &el1, const auto &el2) { return el1->compareTo(*el2); });

    for (const auto &el: birds)
        cout << el->getName() << '\n';
    return 0;
}