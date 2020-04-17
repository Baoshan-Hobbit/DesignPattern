/*************************************************************************
  > File Name: producer_consumer.cc
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年04月15日 星期三 10时15分01秒
 ************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // rand()
#include <unistd.h> // sleep()
#include <vector>

int stock = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t produce_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t consume_cond = PTHREAD_COND_INITIALIZER;

void* Producer(void* arg) {
  while (true) {
    pthread_t tid = pthread_self();
    pthread_mutex_lock(&mutex);
    while (stock >= 10)
      pthread_cond_wait(&produce_cond, &mutex);
    ++stock;
    printf("%u produce, stock: %d\n", (unsigned int)tid, stock); // 加锁后读全局变量
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&consume_cond);
   //sleep(rand() % 3);
  }
  //return nullptr;
}

void* Consumer(void* arg) {
  while (true) {
    pthread_t tid = pthread_self();
    pthread_mutex_lock(&mutex);
    while (stock <= 4)
      pthread_cond_wait(&consume_cond, &mutex);
    --stock;
    printf("%u consume, stock: %d\n", (unsigned int)tid, stock);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&produce_cond);
   //sleep(rand() % 3); //休眠随机时间,方便调试观察
  }
  //return nullptr;
}

void TestAutoLoop() {
  std::vector<int> nums = {1, 2, 8};
  // auto loop 为每个元素创建了拷贝,地址发生变化
  for (int num : nums)
    printf("%p\n", &num);
  for (int i=0; i<nums.size(); ++i)
    printf("%p\n", &nums[i]);
}

int main(int argc, char* argv[]) {
  int num_producer = 4;
  int num_consumer = 2;
  std::vector<pthread_t> producers;
  std::vector<pthread_t> consumers;

  for (int i=0; i<num_producer; ++i) {
    pthread_t producer;
    producers.push_back(producer);
  }
  for (int i=0; i<num_consumer; ++i) {
    pthread_t consumer;
    consumers.push_back(consumer);
  }
  
  //while (true) {
  //  // 不能使用auto loop
  //  for (int i=0; i<producers.size(); ++i) {
  //    pthread_create(&producers[i], nullptr, Producer, nullptr);
  //    pthread_detach(producers[i]); 
  //  }
  //  for (int i=0; i<consumers.size(); ++i) {
  //    pthread_create(&consumers[i], nullptr, Consumer, nullptr);
  //    pthread_detach(consumers[i]);
  //  }
  //}

  // 不能使用auto loop
  for (int i=0; i<producers.size(); ++i) {
    pthread_create(&producers[i], nullptr, Producer, nullptr);
    //pthread_detach(producers[i]); 
  }
  for (int i=0; i<consumers.size(); ++i) {
    pthread_create(&consumers[i], nullptr, Consumer, nullptr);
    //pthread_detach(consumers[i]);
  }

  for (int i=0; i<producers.size(); ++i)
    pthread_join(producers[i], nullptr);
  for (int i=0; i<consumers.size(); ++i)
    pthread_join(consumers[i], nullptr);

//  TestAutoLoop(); 

  return 0;
}
