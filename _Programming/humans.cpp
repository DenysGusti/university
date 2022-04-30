#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Date {
    int day, month, year;

    Date() = default;

    Date(int dd, int mm, int yy) : day{dd}, month{mm}, year{yy} {};

    explicit Date(const string &s) : day{stoi(s.substr(0, 2))}, month{stoi(s.substr(3, 2))},
                                     year{stoi(s.substr(6, 4))} {};

    int countDays() const {
        return year * 360 + month * 30 + day;
    }

    int ageInDays(Date &date) const {
        return date.countDays() - this->countDays();
    }

    string str() const {
        return to_string(day) + '.' + to_string(month) + '.' + to_string(year);
    }
};

struct Human {
    string name, surname;
    Date dateOfBirth{};

    Human() = default;

    Human(string &n, string &s, string &d) : name{n}, surname{s}, dateOfBirth(d) {};
};

int main() {
    fstream f{"humans.txt"};
    size_t n;
    f >> n;
    auto arr = new Human[n];
    for (int i = 0; i < n; ++i) {
        string name, surname, date;
        f >> name >> surname >> date;
        name.pop_back();
        surname.pop_back();
        arr[i] = Human(name, surname, date);
    }

    for (int i = 0; i < n; ++i)
        cout << arr[i].name << ' ' << arr[i].surname << ' ' << arr[i].dateOfBirth.str() << '\n';

    Date today("30.04.2022");
    int age = arr[0].dateOfBirth.ageInDays(today);

    for (int i = 1; i < n; ++i)
        age = max(arr[i].dateOfBirth.ageInDays(today), age);

    for (int i = 0; i < n; ++i)
        if (arr[i].dateOfBirth.ageInDays(today) == age)
            cout << "Людина " << i + 1 << ": " <<
                 arr[i].name << ' ' << arr[i].surname << ' ' << arr[i].dateOfBirth.str() << '\n';

    delete[] arr;
    return 0;
}