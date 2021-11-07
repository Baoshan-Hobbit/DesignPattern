#include <iostream>
#include "exercise.h"

int main() {
  /*
  X<int> x;
  std::cout << x.m1 << std::endl;
  std::cout << x.m2 << std::endl;
  std::cout << x.m3 << std::endl;
  x.f1();
  x.f2();

  Y y;
  std::cout << y.m1 << std::endl;
  std::cout << y.m2 << std::endl;
  std::cout << y.m3 << std::endl;
  std::cout << y.m4 << std::endl;
  */

  Complex<float> cd1;
  Complex<double> cd2(1.0, 2.2);
  Complex<double> cd3(cd1);
  Complex<double> cd4(cd2);
  float a = 1.1;
  float b = 2.2;
  Complex<double> cd5(a, b);

  return 0;
}