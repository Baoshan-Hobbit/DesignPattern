/*************************************************************************
  > File Name: product.cc
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月10日 星期二 16时24分25秒
 ************************************************************************/

#include "src/design_pattern/product.h"
#include <stdio.h>

void Product1::use() const {
  printf("use product1\n");
}
void Product2::use() const {
  printf("use product2\n");
}
