cmake_minimum_required(VERSION 3.10)
project(c_katas C)

set(CMAKE_C_STANDARD 11)

set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})

add_subdirectory(src)
add_subdirectory(test)
