cmake_minimum_required(VERSION 3.17.3)

add_executable(toy_test "")
target_sources(toy_test 
  PRIVATE 
  toy/toy_unittest.cc
  )

target_link_libraries(toy_test PRIVATE design_pattern_lib)
target_link_libraries(toy_test PRIVATE gtest_main)

add_test(
  	NAME demo_test
  	COMMAND $<TARGET_FILE:toy_test>
 )