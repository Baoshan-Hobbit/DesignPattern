#pragma once
#include <cstdint>

class DynBase {
 public:
  virtual uint64_t get_value() const = 0;
  virtual void tick(uint64_t n) = 0;
};

class DynDerived : public DynBase {
 public:
  DynDerived(): counter(0) {}

  virtual uint64_t get_value() const {
    return counter;
  }

  virtual void tick(uint64_t n) {
    counter += n;
  }

 private:
  uint64_t counter;
};

template <typename T>
class CRTP {
 public:
  uint64_t get_value() const {
    return static_cast<const T*>(this)->get_value();
  }

  void tick(uint64_t n) {
    return static_cast<T*>(this)->tick(n);
  }
};

class Derived : public CRTP<Derived> {
 public:
  Derived() : counter(0) {}

  uint64_t get_value() const {
    return counter;
  }

  void tick(uint64_t n) {
    counter += n;
  }

 private:
  uint64_t counter;
};