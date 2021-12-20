#include <iostream>

enum class TrafficLight { Red, Green, Yellow };
enum class Warning { Red, Green, Yellow, Blue };
enum class CharFlag : char { x = 1, y = 2, z = 4 };

void test_switch(Warning warn) {
  switch (warn) {
    case Warning::Red:
      break;
    case Warning::Green:
      break;
    case Warning::Yellow:
      break;
    case Warning::Blue:
      std::cout << "Blue" << std::endl;
      break;
    default:
      break;
  }
}
