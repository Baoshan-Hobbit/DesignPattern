#include <iostream>
#include <memory>
#include <string>

#include "effective_cplus/demo.h"
#include "effective_cplus/inheritage.h"

class Resource {
 public:
  int a_;
};
using ResourcePtr = std::shared_ptr<Resource>;

void set_resource(const ResourcePtr& resource_ptr) {
  resource_ptr->a_ = 5;
}

void test_confused_resource() {
  auto resource_ptr = std::make_shared<Resource>();
  std::cout << resource_ptr->a_ << std::endl;
  set_resource(resource_ptr);
  std::cout << resource_ptr->a_ << std::endl;
}

void test_string() {
  std::u32string str = U"hello中国";
  std::cout << str.c_str() << std::endl;
}

void test_inheritage() {
  std::unique_ptr<Interface> interface_ptr(new Specific());
  interface_ptr->init();
  interface_ptr->pipeline();
  interface_ptr->common_api_func();
}


int main() {
  // test_confused_resource();
  // test_string();
  // print();

  test_inheritage();

  return 0;
}