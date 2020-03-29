/*************************************************************************
  > File Name: product.h
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年03月10日 星期二 16时21分23秒
 ************************************************************************/

#ifndef CODE_PRACTICE_DESIGN_PATTERN_PRODUCT_H_
#define CODE_PRACTICE_DESIGN_PATTERN_PRODUCT_H_ 

#include <string>
#include "src/macro.h"

// c++接口的实现:
// 1) 不显示定义构造函数
// 2) 显示定义虚析构函数(default or {})
// 3) 只有纯虚成员函数
// 4) 只有静态常量数据成员(字面值)
class AbstractProduct {
 public:
  virtual ~AbstractProduct() {} // 显示定义父类虚析构函数,子类可直接调用
  virtual void use() const = 0;  
};

class Product1 : public AbstractProduct {
 public:
  explicit Product1 (std::string name) : name_(name) {}
  DISALLOW_COPY_AND_ASSIGN(Product1);

  void use() const override;
 private:
  std::string name_;
};

class Product2 : public AbstractProduct {
 public:
  explicit Product2 (std::string name) : name_(name) {}
  DISALLOW_COPY_AND_ASSIGN(Product2);

  void use() const override;
 private:
  std::string name_;
};

#endif // CODE_PRACTICE_DESIGN_PATTERN_PRODUCT_H_
