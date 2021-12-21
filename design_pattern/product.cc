#include "design_pattern/product.h"
#include <iostream>

void Product1::use() {
  std::cout << "use " << name_ << std::endl;
}
void Product2::use() {
  std::cout << "use " << name_ << std::endl;
}
