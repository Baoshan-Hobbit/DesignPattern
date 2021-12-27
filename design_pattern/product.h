#pragma once

#include <memory>
#include <string>

// c++接口的实现:
// 1) 不显示定义构造函数
// 2) 显示定义虚析构函数(default or {})
// 3) 只有纯虚成员函数
// 4) 只有静态常量数据成员(字面值)
class AbstractProduct {
 public:
  virtual ~AbstractProduct() = default;  // 显示定义父类虚析构函数,子类可直接调用
  virtual void use() = 0;

  static constexpr const char* kGroup = "DemoProduct";
};

using ProductPtr = std::shared_ptr<AbstractProduct>;

class Product1 : public AbstractProduct {
 public:
  explicit Product1(const std::string& name) : name_(name) {
  }
  void use() override;

 private:
  std::string name_;
};

class Product2 : public AbstractProduct {
 public:
  explicit Product2(const std::string& name) : name_(name) {
  }
  void use() override;

 private:
  std::string name_;
};
