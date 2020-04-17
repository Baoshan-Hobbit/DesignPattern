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
#include "src/macro.h"

void SellFruit(const std::string& name) {
  //printf("sell %s\n", name.c_str());
}

void ThreadPool::AddTask(Task* task) {
  pthread_mutex_lock(&mutex_);
  task_queue_.push_back(task);
  pthread_mutex_unlock(&mutex_);

  pthread_cond_signal(&task_queue_cond_);
}

void ThreadPool::StopAll() {
  for (int i=0; i<pool_size_; ++i)
    pthread_join(thread_pool_[i], nullptr);
}

void ThreadPool::Create() {
 for (int i=0; i<pool_size_; ++i) {
  pthread_t thread;
  thread_pool_.push_back(thread);
 } 
 for (int i=0; i<pool_size_; ++i)
  pthread_create(&thread_pool_[i], nullptr, Run, (void*)this);
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
    printf("pool: %s, %u execute task.\n", ptr->get_name().c_str(), 
        (unsigned int)tid);
    pthread_mutex_unlock(&mutex_);
    sleep(rand() % 3);
  }
}

std::deque<Task*> ThreadPool::task_queue_;
pthread_mutex_t ThreadPool::mutex_ = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ThreadPool::task_queue_cond_ = PTHREAD_COND_INITIALIZER;
