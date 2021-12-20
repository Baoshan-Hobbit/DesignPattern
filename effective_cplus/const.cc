#include <limits>

constexpr int get_int_max() {
  return std::numeric_limits<int>::max();
}

constexpr int max(int a, int b) {
  return a > b ? a : b;
}

// int main() {
//   constexpr bool flag = false;
//   constexpr int ci = 3;
//   constexpr double cd = 3.5;
//   constexpr const char* str = "hello";

//   return 0;
// }