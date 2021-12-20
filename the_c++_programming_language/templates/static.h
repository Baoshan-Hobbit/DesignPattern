#pragma once

#include <iostream>

/*
1. static
*/
template <typename T>
struct X {
  static int m1;            // must define outside class declaration
  static const int m2 = 2;  // may define inside class declaration
  static constexpr int m3 = 3;

  static void f1() {
    std::cout << "f1 called" << std::endl;
  }
  static void f2();
};

template <typename T>
int X<T>::m1 = 1;

struct Y {
  static int m1;
  static const int m2;
  static const int m3 = 3;
  static constexpr int m4 = 4;
};

// must define in header file
template <typename T>
void X<T>::f2() {
  std::cout << "f2 called" << std::endl;
}
