#include "design_pattern/create.h"
#include <stdio.h>
#include <memory>
#include "design_pattern/product.h"

// c++静态语言,即使未使用函数,也会检查函数定义
void TestFactory() {
  // 注意以引用方式调用单例类
  // SimpleFactory& factory = SimpleFactory::GetInstance();
  // std::unique_ptr<AbstractProduct> product(factory.CreateProduct(1));
  //  AbstractFactory* factory = &Factory1::GetInstance();
  //  std::unique_ptr<AbstractProduct> product(factory->CreateProduct());
  //
  // deprecated
  // std::shared_ptr<AbstractProduct> product = factory.CreateProduct(3);
  // std::shared_ptr<AbstractProduct> product = factory->CreateProduct();

  // if (product.get() != nullptr) {
  //  product->use();
  //} else {
  //  printf("create product failed!\n");
  //}

  // Humbger humbger;
  // ConcreteBuilder humbger_builder(&humbger);
  ////humbger_builder.MakeFood();
  ////printf("%s\n", humbger.get_food().c_str());
  // if (humbger_builder.get_humbger()) {
  //  printf("food: %s, drink: %s\n", humbger.get_food().c_str(), humbger.get_drink().c_str());
  //} else {
  //  printf("build failed\n");
  //}

  ConcretePrototype concrete_prototype("bigbigbig", 5);
  Prototype* obj_base = concrete_prototype.Clone();
  ConcretePrototype* obj = dynamic_cast<ConcretePrototype*>(obj_base);
  printf("big_element: %s, type: %d\n", obj->get_big_element().c_str(), obj->get_type());
}

class Unfinished;