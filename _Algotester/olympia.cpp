#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int x, counter = 0;
    cin >> x;
    vector<int> dividers;
    dividers.reserve(24);
    for (int i = 1; i * i <= x; ++i) {
        if (!(x % i)) {
            dividers.push_back(i);
            if (i * i != x)
                dividers.push_back(x / i);
        }
    }
    for (size_t i = 0; i < dividers.size(); ++i)
        for (size_t j = i; j < dividers.size(); ++j)
            if (lcm(dividers[i], dividers[j]) == x) {
                ++counter;
                if (dividers[i] != dividers[j])
                    ++counter;
            }
    cout << counter << endl;
    return 0;
}