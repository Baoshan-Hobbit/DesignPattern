#pragma once

#include <memory>
#include <unordered_map>
#include "design_pattern/product.h"

enum class ProductType {
    PT_A, PT_B, PT_C, Unknown
};

const std::unordered_map<std::string, ProductType> product_type_table = {
    {"PT_A", ProductType::PT_A},
    {"PT_B", ProductType::PT_B},
    {"PT_C", ProductType::PT_C}
};

struct ProductConfig {
    std::string type_name;
    std::string setting;
};

class SimpleFactory {
 public:
  ProductPtr CreateProduct(const ProductConfig& config);
};

class AbstractFactory {
 public:
  virtual ~AbstractFactory() {
  }
  virtual AbstractProduct* CreateProduct() = 0;
  // deprecated
  // virtual std::shared_ptr<AbstractProduct> CreateProduct() = 0;
  // 抽象工厂模式,需要定义AbstractProductA, AbstractProductB
  // 两个抽象产品类
  // virtual std::shared_ptr<AbstractProduct> CreateProductA() = 0;
  // virtual std::shared_ptr<AbstractProduct> CreateProductB() = 0;
};

class Factory1 : public AbstractFactory {
 public:
  static Factory1& GetInstance() {
    static Factory1 inst_factory1;
    return inst_factory1;
  }
  // const是标示函数的一部分,在override之前
  // 具体类都有const关键字，抽象类也要有
  DISALLOW_COPY_AND_ASSIGN(Factory1);

  AbstractProduct* CreateProduct() override;
  // deprecated
  // std::shared_ptr<AbstractProduct> CreateProduct() override;
  // std::shared_ptr<AbstractProduct> CreateProductA() override;
  // std::shared_ptr<AbstractProduct> CreateProductB() override;
 private:
  Factory1() {
  }
};

class Factory2 : public AbstractFactory {
 public:
  static Factory2& GetInstance() {
    static Factory2 inst_factory2;
    return inst_factory2;
  }
  DISALLOW_COPY_AND_ASSIGN(Factory2);

  AbstractProduct* CreateProduct() override;
  // deprecated
  // std::shared_ptr<AbstractProduct> CreateProduct() override;
  // std::shared_ptr<AbstractProduct> CreateProductA() override;
  // std::shared_ptr<AbstractProduct> CreateProductB() override
 private:
  Factory2() {
  }
};

// 建造者模式
class Humbger {
 public:
  Humbger() {
  }
  DISALLOW_COPY_AND_ASSIGN(Humbger);

  void set_food(const std::string& food) {
    food_ = food;
  }
  void set_drink(const std::string& drink) {
    drink_ = drink;
  }
  std::string get_food() const {
    return food_;
  }
  std::string get_drink() const {
    return drink_;
  }

 private:
  std::string food_;
  std::string drink_;
};

class Builder {
 public:
  virtual ~Builder() {
  }
  bool get_humbger() {
    bool food = MakeFood();
    bool drink = MakeDrink();
    return food && drink;
  }

 protected:
  Builder(Humbger* humbger) : humbger_(humbger) {
  }
  virtual bool MakeFood() = 0;
  virtual bool MakeDrink() = 0;

 protected:
  Humbger* humbger_;
};

class ConcreteBuilder : public Builder {
 public:
  ConcreteBuilder(Humbger* humbger) : Builder(humbger) {
  }
  DISALLOW_COPY_AND_ASSIGN(ConcreteBuilder);

 private:
  bool MakeFood() override;
  bool MakeDrink() override;
};

// 原型模式
class Prototype {
 public:
  virtual ~Prototype() {
  }
  virtual Prototype* Clone() = 0;
};

class ConcretePrototype : public Prototype {
 public:
  ConcretePrototype() : type_(1) {
  }
  ConcretePrototype(const std::string& big_element, int type)
      : big_element_(big_element), type_(type) {
  }
  DISALLOW_COPY_AND_ASSIGN(ConcretePrototype);

  void OtherMethod() {
    // printf("other method.\n");
  }
  void set_big_element(const std::string& elem) {
    big_element_ = elem;
  }
  void set_type(int type) {
    type_ = type;
  }
  std::string get_big_element() const {
    return big_element_;
  }
  int get_type() const {
    return type_;
  }
  ConcretePrototype* Clone() override;

 private:
  std::string big_element_;
  int type_;
};
