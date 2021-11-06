#include <iostream>
#include "exercise.h"

int main() {
  X<int> x;
  std::cout << x.m1 << std::endl;
  std::cout << x.m2 << std::endl;
  std::cout << x.m3 << std::endl;
  x.f1();
  x.f2();
  return 0;
}