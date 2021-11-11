#include "member_template.h"
#include "static.h"
#include "crtp.h"

#include <ctime>
#include <functional>
#include <iostream>
#include <chrono>
#include <utility>

constexpr int N = 4000;

void run_dynamic(DynBase* obj_ptr) {
  for (size_t i=0; i<N; ++i) {
    for (size_t j=0; j<i; ++j) {
      obj_ptr->tick(j);
    }
  }
}

/*
  static interface: use base class, for better performance without dynamic virtual table lookup
*/
template <typename T>
void run_crtp(CRTP<T>* obj_ptr) {
  for (size_t i=0; i<N; ++i) {
    for (size_t j=0; j<i; ++j) {
      obj_ptr->tick(j);
    }
  }
}

template <typename FuncType, typename... Args>
void func_wrapper(FuncType f, Args... args) {
  auto start = std::chrono::steady_clock::now();
  f(std::forward<Args>(args)...);
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << "duration: " << duration << " ms" << std::endl;
}

/*
  common method extraction: use concrete class, 
  crtp class main handle common logic abstraction, which have to use other member method.
*/
void run_concrete_a(PartConcreteA* pca_ptr) {
  pca_ptr->scale(2.0);
  std::cout << pca_ptr->get_value() << std::endl;
}

void run_concrete_b(PartConcreteB* pcb_ptr) {
  pcb_ptr->scale(2.0);
  std::cout << pcb_ptr->get_value() << std::endl;
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

  /*
  DynDerived dyn_derived;
  Derived derived;

  run_dynamic(&dyn_derived);
  run_crtp(&derived);

  // -O2 clang, crtp is faster
  func_wrapper(run_dynamic, &dyn_derived);
  func_wrapper(run_crtp<Derived>, &derived);
  */

  PartConcreteA pc_a(1.0);
  PartConcreteB pc_b(2.0);

  func_wrapper(run_concrete_a, &pc_a);
  func_wrapper(run_concrete_b, &pc_b);
  return 0;
}