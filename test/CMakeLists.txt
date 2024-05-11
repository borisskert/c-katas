include(Criterion)

link_directories(${CMAKE_BINARY_DIR}/Criterion)
include_directories(${CMAKE_BINARY_DIR}/Criterion-src/include)

file(GLOB_RECURSE SOURCES *.c)
add_executable(c_katas_test ${SOURCES})
target_link_libraries(c_katas_test c_katas_lib criterion)
add_dependencies(c_katas_test Criterion)
