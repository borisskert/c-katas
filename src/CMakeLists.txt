file(GLOB_RECURSE SOURCES *.c)
add_library(c_katas_lib ${SOURCES})
target_link_libraries(c_katas_lib m)
