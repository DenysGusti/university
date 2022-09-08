#include <iostream>

#include "rectangle.h"

using namespace std;

int main() {
    Rectangle rect({0, 4}, {5, 0});
    cout << rect.getArea() << '\n';
    return 0;
}
