#pragma once

#include <iostream>

template <typename T>
struct X {
  static int m1;
  static const int m2;
  static constexpr int m3 = 3;

  static void f1() {
    std::cout << "f1 called" << std::endl;
  }
  static void f2();
};

template <typename T> int X<T>::m1 = 1;
template <typename T> const int X<T>::m2 = 2;

template <typename T> void X<T>::f2() {
  std::cout << "f2 called" << std::endl;
}