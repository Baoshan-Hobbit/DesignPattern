#pragma once

#include <iostream>
#include <ostream>

/* 
1. static 
*/
template <typename T>
struct X {
  static int m1; // must define outside class declaration
  static const int m2 = 2; // may define inside class declaration
  static constexpr int m3 = 3; 

  static void f1() {
    std::cout << "f1 called" << std::endl;
  }
  static void f2();
};

template <typename T> int X<T>::m1 = 1;

struct Y {
  static int m1;
  static const int m2;
  static const int m3 = 3;
  static constexpr int m4 = 4;
};


// must define in header file
template <typename T> void X<T>::f2() {
  std::cout << "f2 called" << std::endl;
}

/* 
2. member templates

- allow type conversion implicitly happen with use of template.
- default constructor/copy constructor/move constructor generatation rule is 
  complicated, just explicitly declare them.
*/
template <typename Scalar>
class Complex {
 public:
  // Complex() : re{}, im{} {}
  Complex() = default;
  template <typename T>
  Complex(T rr, T ii) : re{rr}, im{ii} {
    std::cout << "constructor with another template type" << std::endl;
  }

  // Complex(const Complex&) = default;
  template <typename T>
  Complex(const Complex<T>& other) : re(other.get_re()), im(other.get_im()) {
    std::cout << "copy constructor with another template type" << std::endl;
  }

  Scalar get_re() const {
    return re;
  }

  Scalar get_im() const {
    return im;
  }

  friend std::ostream& operator<<(std::ostream& ostream, const Complex<Scalar>& cm) {
    ostream << cm.get_re() << "+" << cm.get_im() << "i";
    return ostream;
  }

 private:
  Scalar re;
  Scalar im;
};