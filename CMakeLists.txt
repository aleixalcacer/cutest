cmake_minimum_required(VERSION 3.17)
project(cutest C)

set(CMAKE_C_STANDARD 99)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(examples)
