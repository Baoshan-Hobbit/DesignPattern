#include <iostream>
#include <memory>
#include <string>

class Resource {
 public:
  int a_;
};
using ResourcePtr = std::shared_ptr<Resource>;

void set_resource(const ResourcePtr& resource_ptr) {
  resource_ptr->a_ = 5;
}

void test_string() {
  std::u32string str = U"hello中国";
  std::cout << str.c_str() << std::endl;
}


int main() {
  // auto resource_ptr = std::make_shared<Resource>();
  // std::cout << resource_ptr->a_ << std::endl;
  // set_resource(resource_ptr);
  // std::cout << resource_ptr->a_ << std::endl;

  test_string();
}