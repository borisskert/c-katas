cmake_minimum_required(VERSION 3.10)
project(c_katas C)

set(CMAKE_C_STANDARD 11)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
option (ENABLE_TESTS "Build tests along with the library" ON)

add_subdirectory(src)

if (ENABLE_TESTS)
    find_package (Criterion REQUIRED)

    enable_testing ()
    add_subdirectory (test)
endif ()
