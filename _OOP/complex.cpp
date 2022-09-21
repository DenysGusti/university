#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

using namespace std;
using ld = long double;

class Complex {
private:
    ld re{}, im{};

public:
    // copy constructor, copy-assignment operator, move constructor, move assignment and destructor
    // are compiler-generated

    Complex() = default;

    explicit Complex(const ld re_, const ld im_ = 0) : re{re_}, im{im_} {}

    ld getRe() const noexcept {
        return re;
    }

    void setRe(const ld value) noexcept {
        re = value;
    }

    ld getIm() const noexcept {
        return im;
    }

    void setIm(const ld value) noexcept {
        im = value;
    }

    ld getAbs() const noexcept {
        return hypot(re, im);
    }

    ld getPhi() const noexcept {
        return atan2(im, re);
    }

    friend ostream &operator<<(ostream &os, const Complex &complex) noexcept {
        os << complex.re << '+' << complex.im << 'i';
        return os;
    }

    Complex operator+(const Complex &other) const noexcept {
        return Complex(re + other.re, im + other.im);
    }

    Complex &operator+=(const Complex &other) noexcept {
        re += other.re;
        im += other.im;
        return *this;
    }

    Complex operator-(const Complex &other) const noexcept {
        return Complex(re - other.re, im - other.im);
    }

    Complex &operator-=(const Complex &other) noexcept {
        re -= other.re;
        im -= other.im;
        return *this;
    }

    Complex operator*(const Complex &other) const noexcept {
        return Complex(re * other.re - im * other.im, im * other.re + re * other.im);
    }

    Complex &operator*=(const Complex &other) noexcept {
        ld tmp_re = re * other.re - im * other.im, tmp_im = im * other.re + re * other.im;
        re = tmp_re;
        im = tmp_im;
        return *this;
    }

    Complex operator/(const Complex &other) const {
        if (other.re == 0 && other.im == 0)
            throw overflow_error("ZeroDivisionError");

        ld denom = other.re * other.re + other.im * other.im;

        return Complex((re * other.re + im * other.im) / denom, (im * other.re - re * other.im) / denom);
    }

    Complex &operator/=(const Complex &other) {
        if (other.re == 0 && other.im == 0)
            throw overflow_error("ZeroDivisionError");

        ld denom = other.re * other.re + other.im * other.im;
        ld tmp_re = (re * other.re + im * other.im) / denom, tmp_im = (im * other.re - re * other.im) / denom;
        re = tmp_re;
        im = tmp_im;
        return *this;
    }
};


int main() {
    Complex a(2), b(-2, 1);
    auto c = a + b;
    cout << "a: " << a << "\nb: " << b << "\nc: " << c << endl;
    return 0;
}
