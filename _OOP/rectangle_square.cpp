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

int main() {
    Square sq(3);
    Rectangle rect(4, 5);
    cout << "Square: side = " << sq.getA() << "; area = " << sq.getArea() << "; perimeter = " << sq.getPerimeter()
         << "\nRectangle: width, height = " << rect.getA() << ", " << rect.getB() << "; area = " << rect.getArea()
         << "; perimeter = " << rect.getPerimeter() << endl;
    return 0;
}