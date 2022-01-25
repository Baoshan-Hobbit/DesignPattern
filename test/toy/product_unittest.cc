#include "design_pattern/product.h"
#include "gtest/gtest.h"

void ProcessProduct(AbstractProduct* product_ptr) {
  product_ptr->use();
}

TEST(ProductTest, Product) {
  Product1 product_1("p1");
  Product2 product_2("p2");
  ProcessProduct(&product_1);
  ProcessProduct(&product_2);
  ASSERT_EQ(1, 1);
}
