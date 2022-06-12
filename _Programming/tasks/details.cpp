#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const size_t n = 11, max_number = 10000;
    int code[n] = {7309, 402, 3391, 2611, 402, 7309, 402, 64, 2611, 3391, 5120};
    int hash[max_number]{0};

    for (size_t i = 0; i < n; ++i)
        ++hash[code[i]];

    size_t counter{};
    for (size_t i = 0; i < max_number; ++i)
        if (hash[i]) {
            ++counter;
            cout << setw(4) << setfill('0') << i << ": " << hash[i] << " details\n";
        }
    cout << counter << " different details" << endl;
    return 0;
}