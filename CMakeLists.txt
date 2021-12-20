cmake_minimum_required(VERSION 3.17.3)
project(cplus_practice)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export compile_commands.json

include_directories(${PROJECT_SOURCE_DIR})

aux_source_directory(. main_srcs)
aux_source_directory(effective_cplus effective_cplus_srcs)

add_executable(toy ${main_srcs} ${effective_cplus_srcs})