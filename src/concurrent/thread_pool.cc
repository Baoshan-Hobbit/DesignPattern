/*************************************************************************
  > File Name: thread_pool.h
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年04月16日 星期四 09时29分53秒
 ************************************************************************/

#include "thread_pool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <deque>

void SellFruit(const std::string& name) {
  //printf("sell %s\n", name.c_str());
}

void* ThreadPool::Run(void* arg) {
  ThreadPool* ptr = (ThreadPool*)arg;
  while (true) {
    pthread_t tid = pthread_self();
    pthread_mutex_lock(&mutex_);
    while(task_queue_.empty())
      pthread_cond_wait(&task_queue_cond_, &mutex_);
    Task* task = task_queue_.front();
    task->Run();
    task_queue_.pop_front();
    // 有时反应不过来会出现重复写的情形,原因待查
    printf("pool: %s, %u execute task.\n", ptr->name_.c_str(), 
        (unsigned int)tid);
    pthread_mutex_unlock(&mutex_);
    sleep(rand() % 3); // 便于观察,debug用
  }
}

void ThreadPool::StopAll() {
  if (!is_running_) {
    printf("Alreaady stopped!\n");
    return;
  }
  printf("pool size: %d\n", (int)thread_pool_.size());
  for (int i=0; i<thread_pool_.size(); ++i)
    pthread_join(thread_pool_[i], nullptr);
}

std::deque<Task*> ThreadPool::task_queue_;
pthread_mutex_t ThreadPool::mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::task_queue_cond_ = PTHREAD_COND_INITIALIZER;

void FixedThreadPool::AddTask(Task* task) {
  pthread_mutex_lock(&mutex_);
  task_queue_.push_back(task);
  pthread_mutex_unlock(&mutex_);

  pthread_cond_signal(&task_queue_cond_);
}

void FixedThreadPool::Create() {
  for (int i=0; i<core_pool_size_; ++i) {
    pthread_t thread;
    pthread_create(&thread, nullptr, Run, (void*)this);
    thread_pool_.push_back(thread);
  } 
  is_running_ = true;
}

void DynamicThreadPool::AddTask(Task* task) {
  bool core_not_full = thread_pool_.size() < core_pool_size_;
  bool max_not_full = (thread_pool_.size() >= core_pool_size_) &&
                      (task_queue_.size() >= queue_size_)     &&
                      (thread_pool_.size() < max_pool_size_);
  if (core_not_full || max_not_full)
    Create();

  pthread_mutex_lock(&mutex_);
  task_queue_.push_back(task);
  pthread_mutex_unlock(&mutex_);

  pthread_cond_signal(&task_queue_cond_);
}

void DynamicThreadPool::Create() {
  pthread_t thread;
  pthread_create(&thread, nullptr, Run, (void*)this);
  thread_pool_.push_back(thread);
}
