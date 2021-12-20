#pragma once

#include <string>
#include "macro.h"

// c++接口的实现:
// 1) 不显示定义构造函数
// 2) 显示定义虚析构函数(default or {})
// 3) 只有纯虚成员函数
// 4) 只有静态常量数据成员(字面值)
class AbstractProduct {
 public:
  virtual ~AbstractProduct() {
  }  // 显示定义父类虚析构函数,子类可直接调用
  virtual void use() = 0;
};

class Product1 : public AbstractProduct {
 public:
  explicit Product1(std::string name) : name_(name) {
  }
  DISALLOW_COPY_AND_ASSIGN(Product1);

  void use() override;

 private:
  std::string name_;
};

class Product2 : public AbstractProduct {
 public:
  explicit Product2(std::string name) : name_(name) {
  }
  DISALLOW_COPY_AND_ASSIGN(Product2);

  void use() override;

 private:
  std::string name_;
};
