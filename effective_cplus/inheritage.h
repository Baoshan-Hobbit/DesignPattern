#pragma once

/**
* 1. 单一职责原则，每个类只完成一件事情
* 2. 显示使用 virtual override，表示接口覆盖
*/

/**
 * @brief 显式定义 api: pipeline
*/
class Interface {
 public:
  virtual ~Interface() = default;
  virtual void pipeline() = 0;
  virtual void common_api_func() = 0;
};

/**
 * @brief 实现 pipeline,并定义 pipeline 内部接口,内部接口一律使用 protected 关键字
*/
class Base : public Interface {
 public:
  virtual ~Base() = default;
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
  General();
  virtual ~General() = default;
  virtual void common_api_func() override;

 protected:
  // pipeline 的每一步的默认实现 
  virtual void pre_process() override;
  virtual void process() override;
  virtual void post_process() override;
};

class Specific : public General {
 public:
  Specific();
  ~Specific() = default;
 
 protected:
  virtual void pre_process() override; // 可在默认实现上增加逻辑
  virtual void post_process() override; // 可修改默认实现的逻辑
};
