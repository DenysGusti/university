#ifndef UNIVERSITY_NAMED_OBJECT_HPP
#define UNIVERSITY_NAMED_OBJECT_HPP

#include <string>

using namespace std;

class NamedObject {
protected:
    string name;

public:
    NamedObject() = default;

    explicit NamedObject(string_view name_) : name{name_} {}

    virtual ~NamedObject() = default;

    string getName() const noexcept {
        return name;
    }

    void setName(string_view name_) noexcept {
        name = name_;
    }
};

#endif
