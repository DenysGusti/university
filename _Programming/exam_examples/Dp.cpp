#include <iostream>
#include <fstream>

using namespace std;

struct Date {
    int d{}, m{};

    Date() = default;

    explicit Date(char *date) : d{(date[0] - '0') * 10 + date[1] - '0'}, m{(date[2] - '0') * 10 + date[3] - '0'} {}

    void print() const {
        cout << (d > 10 ? "" : "0") << d << (m > 10 ? "" : "0") << m << '\n';
    }

    int countDays() const {
        int days{};
        switch (m) {
            case 12:
                days += 30;
            case 11:
                days += 31;
            case 10:
                days += 30;
            case 9:
                days += 31;
            case 8:
                days += 31;
            case 7:
                days += 30;
            case 6:
                days += 31;
            case 5:
                days += 30;
            case 4:
                days += 31;
            case 3:
                days += 28;
            case 2:
                days += 31;
            case 1:
                days += 0;
        }
        days += d;
        return days;
    }

    int findDays(const Date &other) const {
        return abs(countDays() - other.countDays()) + 1;
    }
};

int main() {
    ifstream fin{R"(C:\Users\denys\CLionProjects\University\university\_Programming\exam_examples\problemin.txt)"};
    const int tests = 2;
    Date dates[2 * tests];
    cout << "Input:\n";
    for (size_t i = 0; i < 2 * tests; ++i) {
        char buf[5];
        fin >> buf;
        dates[i] = Date(buf);
        dates[i].print();
        if (i % 2)
            cout << '\n';
    }

    cout << "Output:\n";
    for (size_t i = 0; i < 2 * tests; i += 2) {
        int days = dates[i].findDays(dates[i + 1]);
        cout << days << "\n\n";
    }
    return 0;
}