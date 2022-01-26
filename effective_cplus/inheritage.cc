#include "effective_cplus/inheritage.h"

#include <string>
#include <iostream>

void Base::pipeline() {
  pre_process();
  process();
  post_process();
}

void Interface::common_api_func() {
  std::cout << "common api func" << std::endl;
}

General::General() {
  std::cout << "general init, common logic" << std::endl;
}

void General::pre_process() {
  std::cout << "general pre_process" << std::endl;
}

void General::process() {
  std::cout << "general process" << std::endl;
}

void General::post_process() {
  std::cout << "general post_process" << std::endl;
}

Specific::Specific() : General() {
  std::cout << "specific init, personal logic" << std::endl;
}

void Specific::pre_process() {
  General::pre_process();
  std::cout << "specific pre_process, personal added logic" << std::endl;
}

void Specific::post_process() {
  std::cout << "specific post_process, personal altered logic" << std::endl;
}