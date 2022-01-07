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


bool General::init() {
  std::cout << "general init, common logic" << std::endl;
  return do_init();
}

bool General::do_init() {
  return true; // do nothing
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


bool Specific::do_init() {
  std::cout << "specific init, personal logic" << std::endl;
  return true;
}

void Specific::pre_process() {
  General::pre_process();
  std::cout << "specific pre_process, personal added logic" << std::endl;
}

void Specific::post_process() {
  std::cout << "specific post_process, personal altered logic" << std::endl;
}