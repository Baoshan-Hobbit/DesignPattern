/*************************************************************************
  > File Name: thread_pool.h
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年04月17日 星期五 15时53分43秒
 ************************************************************************/

#ifndef CPLUS_PRACTICE_CONCURRENT_THREADPOOL_H_
#define CPLUS_PRACTICE_CONCURRENT_THREADPOOL_H_

#include <pthread.h>
#include <limits.h>
#include <string>
#include <deque>
#include <vector>
#include "src/macro.h"

void SellFruit(const std::string& name);

class Task {
 public:
  virtual ~Task() {}
  virtual void Run() = 0;
};

class SellTask : public Task {
 public:
  //构造函数中需要SellType,隐含外部传进的参数被定义为此类型,因此定义为public
  typedef void (*SellType)(const std::string&); 

  SellTask(SellType sell, const std::string& data) : sell_(sell), data_(data) {}
  void Run() override { sell_(data_); }

 private:
  std::string data_;
  SellType sell_;
};

class ThreadPool {
 public:
  ThreadPool(int core_pool_size, int max_pool_size, int queue_size) : 
             core_pool_size_(core_pool_size), 
             max_pool_size_(max_pool_size), 
             queue_size_(queue_size) {} 
  virtual ~ThreadPool() {}

  virtual void AddTask(Task* task) = 0;
  void StopAll();
  void set_name(const std::string& name) { name_ = name; }

 protected:
  virtual void Create() = 0;
  static void* Run(void* arg);

 protected:
  int core_pool_size_;
  int max_pool_size_;
  int queue_size_;
  // 理解多个线程之间共享数据:
  // 在一个文件的范围内,多个线程执行同样的函数,该函数访问数据,该数据对不同函数
  // 是共享的,因此从编程的逻辑来看数据的共享不是执行同一个函数的多个线程对函数内
  // 定义的变量的共享,而是多个函数的共享
  // 命名空间与文件对应,类与函数对应,类中的数据成员相当于函数内的局部变量,多个
  // 线程执行同一个类的成员函数(当然必须为static函数),共享的数据应当是不同类共享
  // 的数据,因此需要声明为static,类内成员函数对数据成员的共享是类相比于函数额外
  // 增加的优势
  static std::deque<Task*> task_queue_;
  static pthread_mutex_t mutex_;
  static pthread_cond_t task_queue_cond_;
  std::vector<pthread_t> thread_pool_;
  std::string name_;
};

class FixedThreadPool : public ThreadPool {
 public:
  explicit FixedThreadPool(int pool_size) : ThreadPool(pool_size, pool_size, 
                                              INT_MAX) { Create(); } 
  void AddTask(Task* task) override;
  DISALLOW_COPY_AND_ASSIGN(FixedThreadPool);

 private:
  void Create() override;
};

class DynamicThreadPool : public ThreadPool {
 public:
  explicit DynamicThreadPool(int core_pool_size, 
                             int max_pool_size, 
                             int queue_size) : 
                                              ThreadPool(core_pool_size, 
                                                         max_pool_size, 
                                                         queue_size) {}
  void AddTask(Task* task) override;
  DISALLOW_COPY_AND_ASSIGN(DynamicThreadPool);

 private:
  void Create() override;
};

#endif //CPLUS_PRACTICE_CONCURRENT_THREADPOOL_H_
