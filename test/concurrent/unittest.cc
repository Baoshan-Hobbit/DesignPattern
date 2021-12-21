#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

#include "concurrent/thread_pool.h"

void TestIntToString() {
  char str[10];
  s  // printf(str, "%d", 2);
      // printf("%s\n", str);
      std::string apple = "apple_" + std::string(str);
  // printf("%s\n", apple.c_str());
}

void TestThreadPool() {
  std::vector<SellTask> task_list_1;
  // std::vector<SellTask> task_list_2;
  for (int i = 0; i < 10; ++i) {
    char str[10];
    s  // printf(str, "%d", i);
        std::string apple = "apple_" + std::string(str);
    // std::string xigua = "xigua_" + std::string(str);
    SellTask sell_task_1(SellFruit, apple);
    // SellTask sell_task_2(SellFruit, xigua);
    task_list_1.push_back(sell_task_1);
    // task_list_2.push_back(sell_task_2);
  }

  FixedThreadPool thread_pool_1(3);
  // DynamicThreadPool thread_pool_1(2, 5, 8);
  // ThreadPool thread_pool_2(3);
  // ThreadPool thread_pool_1(2, 5, 8);
  thread_pool_1.set_name("pool_1");
  // thread_pool_2.set_name("pool_2");

  for (int i = 0; i < task_list_1.size(); ++i) {
    // AddTask形参为指针,实参应当取地址符而非子类对象的指针
    thread_pool_1.AddTask(&task_list_1[i]);
    // thread_pool_2.AddTask(&task_list_2[i]);
  }

  // sleep(5);
  // 不用static成员变量随机输出结果,原因待查TODO
  thread_pool_1.StopAll();
  // thread_pool_1.StopAll();
  // thread_pool_2.StopAll();
}

class Foo {
 public:
  Foo(int a) : a_(a) {
  }
  static void func(void* arg) {
    Foo* ptr = (Foo*)arg;
    int a = ptr->a_;
    // printf("%d\n", a);
  }

 private:
  int a_;
};
