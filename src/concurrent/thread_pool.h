/*************************************************************************
  > File Name: thread_pool.h
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年04月17日 星期五 15时53分43秒
 ************************************************************************/

#ifndef CPLUS_PRACTICE_CONCURRENT_THREADPOOL_H_
#define CPLUS_PRACTICE_CONCURRENT_THREADPOOL_H_

#include <pthread.h>
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
  explicit ThreadPool(int pool_size) : pool_size_(pool_size) { Create(); } 
  void AddTask(Task* task);
  void StopAll();

  void set_name(const std::string& name) { name_ = name; }
  std::string get_name() const { return name_; }

  DISALLOW_COPY_AND_ASSIGN(ThreadPool);

 private:
  void Create();
  static void* Run(void* arg);

 private:
  int pool_size_;
  static std::deque<Task*> task_queue_;
  static pthread_mutex_t mutex_;
  static pthread_cond_t task_queue_cond_;
  std::vector<pthread_t> thread_pool_;
  std::string name_;
};

#endif //CPLUS_PRACTICE_CONCURRENT_THREADPOOL_H_
