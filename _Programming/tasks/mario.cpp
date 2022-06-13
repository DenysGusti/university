#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int h{};
    cout << "height: ";
    cin >> h;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < h + 2; ++j)
            cout << (j < h + 1 ? (j < h - i - 1 ? ' ' : '#') : '\n');
    return 0;
}