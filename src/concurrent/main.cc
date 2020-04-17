/*************************************************************************
  > File Name: main.cc
  > Author: baoshan
  > Mail: baoshanw@foxmail.com 
  > Created Time: 2020年04月17日 星期五 16时03分46秒
 ************************************************************************/

#include <stdio.h>
#include <string>
#include <vector>
#include "thread_pool.h"

void TestIntToString() {
  char str[10];
  sprintf(str, "%d", 2);
  printf("%s\n", str);
  std::string apple = "apple_" + std::string(str);
  printf("%s\n", apple.c_str());
}

void TestThreadPool() {
  std::vector<SellTask> task_list_1;
  std::vector<SellTask> task_list_2;
  for (int i=0; i<10; ++i) {
    char str[10];
    sprintf(str, "%d", i);
    std::string apple = "apple_" + std::string(str);
    std::string xigua = "xigua_" + std::string(str);
    SellTask sell_task_1(SellFruit, apple);
    SellTask sell_task_2(SellFruit, xigua);
    task_list_1.push_back(sell_task_1);
    task_list_2.push_back(sell_task_2);
  }

  ThreadPool thread_pool_1(3);
  ThreadPool thread_pool_2(3);
  thread_pool_1.set_name("pool_1");
  thread_pool_2.set_name("pool_2");
  for (int i=0; i<task_list_1.size(); ++i) {
    // AddTask形参为指针,实参应当取地址符而非子类对象的指针
    thread_pool_1.AddTask(&task_list_1[i]);
    thread_pool_2.AddTask(&task_list_2[i]);
  }
  thread_pool_1.StopAll();
  thread_pool_2.StopAll();
}

int main(int argc, char* argv[]) {
  //TestIntToString();
  TestThreadPool();
}
