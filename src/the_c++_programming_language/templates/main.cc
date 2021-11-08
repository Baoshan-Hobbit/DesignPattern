#include "member_template.h"
#include "static.h"
#include "crtp.h"

#include <ctime>
#include <functional>
#include <iostream>
#include <chrono>
#include <utility>

void run_dynamic(DynBase* obj_ptr) {
  const size_t N = 4000;
  for (size_t i=0; i<N; ++i) {
    for (size_t j=0; j<i; ++j) {
      obj_ptr->tick(j);
    }
  }
}

template <typename T>
void run_crtp(CRTP<T>* obj_ptr) {
  const size_t N = 4000;
  for (size_t i=0; i<N; ++i) {
    for (size_t j=0; j<i; ++j) {
      obj_ptr->tick(j);
    }
  }
}

template <typename FuncType, typename... Args>
void run_benchmark(FuncType f, Args... args) {
  auto start = std::chrono::steady_clock::now();
  f(std::forward<Args>(args)...);
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "duration: " << duration << " ms" << std::endl;
}

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

  /*
  Complex<float> cd1;
  Complex<double> cd2(1.0, 2.2);
  Complex<double> cd3(cd1);
  Complex<double> cd4(cd2);
  float a = 1.1;
  float b = 2.2;
  Complex<double> cd5(a, b);
  */

  DynDerived dyn_derived;
  Derived derived;

  run_dynamic(&dyn_derived);
  run_crtp(&derived);

  // -O2 clang, crtp is faster
  run_benchmark(run_dynamic, &dyn_derived);
  run_benchmark(run_crtp<Derived>, &derived);

  return 0;
}