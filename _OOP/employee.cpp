#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    int id{};

public:
    Employee(string_view name_, int id_) : name{name_}, id{id_} {
        cout << "constructor Employee() done" << endl;
    }

    ~Employee() {
        cout << "destructor ~Employee() done" << endl;
    }

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    string toString() const {
        return "\nEmployee: name = " + getName() + ", id = " + to_string(getId());
    }

    bool operator <(const Employee&other) const {
        return id < other.id;
    }
};


class Operation {
public:
    static Employee* getMax(Employee *arr, const size_t n) {
        Employee *result = arr;
        for (size_t i = 0; i < n; ++i)
            if (*result < arr[i])
                result = arr + i;
        return result;
    }
};

int main() {
    Employee arr[]{{"Ivan", 4}, {"Petro", 2}};  // no use using heap array with heap objects
    const size_t n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original Array:  ";
    for (size_t i = 0; i < n; ++i)
        cout << arr[i].toString() << ' ';

    auto maxEmployee = Operation::getMax(arr, n);
    cout << "\nmax employee: " << maxEmployee->toString();

    cout << "\ndone" << endl;
    return 0;
}