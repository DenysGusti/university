#include <iostream>
#include <string>

using namespace std;

int main() {
    string beards = "brbrrrbbbrrrrrbrrbbrbbbbrrrrb";
    const size_t n = beards.length();

    for (beards.reserve(n + 1); beards[0] == beards[n - 1]; beards += beards[0], beards = beards.substr(1, n)) {}

    size_t max_quantity = 0;
    char current = beards.front();
    for (size_t prev_length = 0, prev = 0, i = 0; i <= n; ++i)
        if (beards[i % n] != current) {
            max_quantity = max(prev_length + i - prev, max_quantity);
            prev_length = i - prev;
            prev = i;
            current = current == 'b' ? 'r' : 'b';
        }

    cout << "N = " << n << '\n' << beards << '\n' << max_quantity << endl;
    return 0;
}