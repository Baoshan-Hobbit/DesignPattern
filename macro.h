#pragma once

// macro 难以调试,如果名字写错会报错ISO C++ forbids declaration of *** with
// no type,没半毛钱关系
// 尤其要注意把参数写上,经常忘记写
#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
  ClassName(const ClassName&) = delete;     \
  ClassName& operator=(const ClassName&) = delete
