cmake_minimum_required(VERSION 3.17.3)
project(cplus_practice)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compile_commands.json

################ build bin ################
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(. main_srcs)
aux_source_directory(effective_cplus effective_cplus_srcs)
file(GLOB_RECURSE factory_practice_srcs RELATIVE ${CMAKE_SOURCE_DIR} "design_pattern/factory_practice/*.cc")

add_library(design_pattern_lib STATIC design_pattern/product.cc)
add_executable(main ${main_srcs} ${effective_cplus_srcs} ${factory_practice_srcs})

enable_testing()

################ build unittest ################
set(BUILD_TESTING OFF)
if (DEFINED ENV{BUILD_TESTING})
  message(STATUS "use env BUILD_TESTING: $ENV{BUILD_TESTING}")
  set(BUILD_TESTING $ENV{BUILD_TESTING})
endif ()

if (BUILD_TESTING)
  message(STATUS "BUILD_TESTING: ON")

  ################ download gtest ################
  include(FetchContent)
  FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG release-1.10.0
  )
  FetchContent_MakeAvailable(googletest)

  add_subdirectory(test)
endif ()