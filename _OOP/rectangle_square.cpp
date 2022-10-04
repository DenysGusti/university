#include <iostream>

using namespace std;
using ld = long double;

/*
If Square inherits Rectangle, it will violate the Liskov substitution principle, one of the SOLID principles, that says
that if a program module is using a base class, then the reference to the base class can be replaced with a derived
class without affecting the functionality of the program module. In our case, if Square inherits Rectangle and some
function accepts Square as Rectangle reference, after setA(5) and setB(4), getArea() will be 16, not 20. One of the
solutions to this would be to reverse the inheritance.
*/

class Square {
protected:
    ld a{};
public:
    Square() = default;

    explicit Square(const ld a_) : a{a_} {}

    ld getA() const noexcept {
        return a;
    }

    void setA(const ld value) noexcept {
        a = value;
    }

    virtual ld getArea() const noexcept {
        return a * a;
    }

    virtual ld getPerimeter() const noexcept {
        return 4 * a;
    }
};

class Rectangle : public Square {
protected:
    ld b{};
public:
    Rectangle() = default;

    Rectangle(const ld a_, const ld b_) : Square(a_), b{b_} {}

    ld getB() const noexcept {
        return b;
    }

    void setB(const ld value) noexcept {
        b = value;
    }

    ld getArea() const noexcept override {
        return a * b;
    }

    ld getPerimeter() const noexcept override {
        return 2 * (a + b);
    }
};

size_t maxArea(Square **arr, const size_t n) {
    size_t k = 0;
    auto area = arr[k]->getArea();
    for (size_t i = 1; i < n; ++i)
        if (arr[i]->getArea() > area) {
            area = arr[i]->getArea();
            k = i;
        }
    return k;
}

size_t maxPerimeter(Square **arr, const size_t n) {
    size_t k = 0;
    auto perimeter = arr[k]->getPerimeter();
    for (size_t i = 1; i < n; ++i)
        if (arr[i]->getPerimeter() > perimeter) {
            perimeter = arr[i]->getPerimeter();
            k = i;
        }
    return k;
}

int main() {
    auto arr = new Square *[]{new Rectangle(2, 7), new Square(4), new Rectangle(3, 5), new Square(3)};
    const size_t n = 4;

    size_t max_area_idx = maxArea(arr, n), max_perimeter_idx = maxPerimeter(arr, n);

    cout << "max area: arr[" << max_area_idx << "] - " << arr[max_area_idx]->getArea()
         << "\nmax perimeter: arr[" << max_perimeter_idx << "] - " << arr[max_perimeter_idx]->getPerimeter() << endl;

    for (size_t i = 0; i < n; ++i)
        delete arr[i];
    delete[] arr;
    return 0;
}