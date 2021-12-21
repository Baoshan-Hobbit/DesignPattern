cmake_minimum_required(VERSION 3.17.3)
project(cplus_practice)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compile_commands.json

################ build bin ################
include_directories(${PROJECT_SOURCE_DIR})
aux_source_directory(. main_srcs)
aux_source_directory(effective_cplus effective_cplus_srcs)

add_library(design_pattern_lib STATIC design_pattern/product.cc)
add_executable(toy ${main_srcs} ${effective_cplus_srcs})

enable_testing()

################ download gtest ################
include(FetchContent)
FetchContent_Declare(
  	googletest
  	GIT_REPOSITORY https://github.com/google/googletest.git
  	GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

################ build unittest ################
set(BUILD_TESTING ON)
if (DEFINED ENV{BUILD_TESTING})
  message(STATUS "use env BUILD_TESTING: $ENV{BUILD_TESTING}")
  set(BUILD_TESTING $ENV{BUILD_TESTING})
endif ()

if (BUILD_TESTING)
  message(STATUS "BUILD_TESTING: ON")
  add_subdirectory(test)
endif ()