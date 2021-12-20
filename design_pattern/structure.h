#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "design_pattern/product.h"
#include "macro.h"

// 外观模式
class Facade {
 public:
  explicit Facade(const std::string& name);
  DISALLOW_COPY_AND_ASSIGN(Facade);

  void WrapOperation() const;

 private:
  std::string name_;
  std::unique_ptr<Product1> product1_;
  std::unique_ptr<Product2> product2_;
};

// 透明组合模式
class TransparentComponent {
 public:
  virtual ~TransparentComponent() {
  }

  virtual void Add(TransparentComponent* component) = 0;
  virtual void Remove() = 0;
  virtual void Display() = 0;
};

class TransparentFile : public TransparentComponent {
 public:
  explicit TransparentFile(const std::string& name) : name_(name) {
  }
  DISALLOW_COPY_AND_ASSIGN(TransparentFile);

  void Add(TransparentComponent* component) override;
  void Remove() override;
  void Display() override;

 private:
  std::string name_;
};

class TransparentFolder : public TransparentComponent {
 public:
  TransparentFolder(const std::string& name) : name_(name), level_(1) {
  }
  DISALLOW_COPY_AND_ASSIGN(TransparentFolder);

  void Add(TransparentComponent* component) override;
  void Remove() override;
  void Display() override;

 public:
  int level_;

 private:
  std::string name_;
  std::vector<TransparentComponent*> composite_list_;
};

// 安全组合模式
class SafeComponent {
 public:
  virtual ~SafeComponent() {
  }
  virtual void Display() = 0;
};

class SafeFile : public SafeComponent {
 public:
  explicit SafeFile(const std::string& name) : name_(name) {
  }
  DISALLOW_COPY_AND_ASSIGN(SafeFile);

  void Display() override;

 private:
  std::string name_;
};

class SafeFolder : public SafeComponent {
 public:
  explicit SafeFolder(const std::string& name) : name_(name), level_(1) {
  }
  DISALLOW_COPY_AND_ASSIGN(SafeFolder);

  void Add(SafeComponent* component);
  void Remove();
  void Display() override;

 public:
  int level_;

 private:
  std::string name_;
  // 默认初始化,类似全局变量的初始化,类相当于全局作用域
  // 可在类的数据成员中使用自身类的指针, 因为指针可以指向一个
  // 只声明却还未定义的类
  std::vector<SafeComponent*> composite_list_;
};

// 适配器模式
class Target {
 public:
  virtual ~Target() {
  }
  virtual void Request() = 0;
};

class Adaptee {
 public:
  explicit Adaptee(const std::string& str);
  DISALLOW_COPY_AND_ASSIGN(Adaptee);

  void OldRequest();

 private:
  std::string adaptee_member_;
};

// 对象结构型适配器
class Adapter : public Target {
 public:
  explicit Adapter(Adaptee* adaptee);
  DISALLOW_COPY_AND_ASSIGN(Adapter);

  void Request() override;

 private:
  Adaptee* adaptee_;
};

// 类结构型适配器
// private Adaptee目的是限制OldRequest()接口通过Adapter2的调用
// 不符合google一律public继承的原则
class Adapter2 : public Target, private Adaptee {
 public:
  explicit Adapter2(const std::string& str);
  DISALLOW_COPY_AND_ASSIGN(Adapter2);

  void Request() override;
};

// 代理模式
class Subject {
 public:
  virtual ~Subject() {
  }
  virtual void Request() = 0;
};

class RealSubject : public Subject {
 public:
  RealSubject() {
  }
  void Request() override;
};

// 静态代理
// TODO: 动态代理
class Proxy : public Subject {
 public:
  Proxy() : real_subject_(new RealSubject()) {
  }
  DISALLOW_COPY_AND_ASSIGN(Proxy);

  void Request() override;

 private:
  void PreRequest() {
    printf("Before request.\n");
  }
  void AfterRequest() {
    printf("After request.\n");
  }

 private:
  std::unique_ptr<RealSubject> real_subject_;
};

// 桥接模式
class Implementor {
 public:
  virtual ~Implementor() {
  }
  virtual void Implement() = 0;
};

class Abstraction {
 public:
  virtual ~Abstraction() {
  }
  virtual void Operate() = 0;

 protected:
  explicit Abstraction(Implementor* impl) : impl_(impl) {
  }
  void OperateImplementor();

 private:
  Implementor* impl_;
};

class RefinedAbstraction : public Abstraction {
 public:
  explicit RefinedAbstraction(Implementor* impl) : Abstraction(impl) {
  }
  DISALLOW_COPY_AND_ASSIGN(RefinedAbstraction);

  void Operate() override;
};

class ConcreteImplementor : public Implementor {
 public:
  ConcreteImplementor() {
  }
  void Implement() override;
};

// 装饰模式
class Component {
 public:
  virtual ~Component() {
  }
  virtual void Operate() = 0;
};

class ConcreteComponent : public Component {
 public:
  ConcreteComponent() {
  }
  void Operate() override;
};

class Decorator : public Component {
 public:
  virtual ~Decorator() {
  }
  virtual void Operate() = 0;

 protected:
  explicit Decorator(Component* component) : component_(component) {
  }
  void OperateComponent() {
    component_->Operate();
  }

 private:
  Component* component_;
};

class ConcreteDecorator : public Decorator {
 public:
  explicit ConcreteDecorator(Component* component) : Decorator(component) {
  }
  DISALLOW_COPY_AND_ASSIGN(ConcreteDecorator);

  void Operate() override;

 private:
  void AddProperty();
};

// 享元模式
class FlyWeight {
 public:
  virtual ~FlyWeight() {
  }
  virtual void Operate(const std::string& external) = 0;

 protected:
  explicit FlyWeight(const std::string& internal) {
    internal_ = internal;
  }

 protected:
  std::string internal_;
};

class ConcreteFlyWeight : public FlyWeight {
 public:
  explicit ConcreteFlyWeight(const std::string& internal) : FlyWeight(internal) {
  }
  DISALLOW_COPY_AND_ASSIGN(ConcreteFlyWeight);

  void Operate(const std::string& external) override;
};

class CachedFactory {
 public:
  static CachedFactory& GetInstance() {
    static CachedFactory factory;
    return factory;
  }
  DISALLOW_COPY_AND_ASSIGN(CachedFactory);

  FlyWeight* CreateFlyWeight(const std::string& arg);
  size_t get_count() const {
    return fly_weight_pool_.size();
  }

 private:
  CachedFactory() {
  }  // 一定要定义,否则会报错"未定义的引用"
  std::map<std::string, FlyWeight*> fly_weight_pool_;
};
