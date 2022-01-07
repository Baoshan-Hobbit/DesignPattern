#pragma once

/**
* 1. 单一职责原则，每个类只完成一件事情
* 2. 显示使用 virtual override，表示接口覆盖
*/

/**
 * @brief 显式定义 api: init && pipeline
*/
class Interface {
 public:
  Interface() = default;
  virtual ~Interface() = default;

 public:
  virtual bool init() = 0;
  virtual void pipeline() = 0;
 
 public:
  void common_api_func();

 private:
  int mem_a_;
};

/**
 * @brief 实现 pipeline,并定义 pipeline 内部接口,内部接口一律使用 protected 关键字
*/
class Base : public Interface {
 public:
  Base() = default;
  virtual ~Base() = default;

 public:
  virtual void pipeline() override;

 protected:
  virtual void pre_process() = 0;
  virtual void process() = 0;
  virtual void post_process() = 0;
};

/**
 * @brief 通用实现 
*/
class General : public Base {
 public:
  General() = default;
  virtual ~General() = default;

 public:
  virtual bool init() override; // 抽象出子类的公共初始化逻辑

 protected:
  virtual bool do_init(); // do nothing

 protected:
  // pipeline 的每一步的默认实现 
  virtual void pre_process() override;
  virtual void process() override;
  virtual void post_process() override;
};

class Specific : public General {
 public:
  Specific() = default;
  ~Specific() = default;
 
 protected:
  virtual bool do_init() override; // 子类特有的初始化逻辑

 protected:
  virtual void pre_process() override; // 可在默认实现上增加逻辑
  virtual void post_process() override; // 可修改默认实现的逻辑
};
