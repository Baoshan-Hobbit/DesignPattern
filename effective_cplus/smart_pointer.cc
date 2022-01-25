#include "effective_cplus/smart_pointer.h"
#include <iostream>
#include <memory>

namespace smart_pointer {

Derived::Derived() {
  std::cout << "construct derived" << std::endl;
}
Derived::~Derived() {
  std::cout << "destruct derived" << std::endl;
}

void local_unique_ptr() {
  // 局部变量，没必要使用 shared_ptr
  auto ptr = std::make_unique<Derived>();
}

void update_by_pointer(Base* ptr) {
  if (!ptr) {
    return;
  }
  ptr->a_ = 3;
  std::cout << ptr->a_ << std::endl;
}

void read_by_pointer(const Base* ptr) {
  if (!ptr) {
    return;
  }
  std::cout << ptr->a_ << std::endl;
}

void update_by_ref(Base& base) {
  base.a_ = 5;
  std::cout << base.a_ << std::endl;
}

void read_by_ref(const Base& base) {
  std::cout << base.a_ << std::endl;
}

void sink(std::unique_ptr<Base> ptr) {
  ptr.reset();
}

void modify_unique_ownership(std::unique_ptr<Derived>& ptr) {
  ptr.reset(new Derived());
}

void bad(const std::unique_ptr<Derived>& ptr) {
  std::cout << "bad" << std::endl;
}

void share_ownership(std::shared_ptr<Base> ptr) {
  const auto& another_ptr = ptr;
  std::cout << "todo later" << std::endl;
}

void maybe_inner_share_ownership(const std::shared_ptr<Derived>& ptr) {
  const auto& another_ptr = ptr;
  std::cout << "todo later" << std::endl;
}

void modify_shared_ownership(std::shared_ptr<Derived>& ptr) {
  ptr.reset();
}

std::unique_ptr<Base> get_unique_ptr() {
  return std::make_unique<Derived>();
}

std::shared_ptr<Base> get_shared_ptr() {
  return std::make_shared<Derived>();
}

}  // namespace smart_pointer;