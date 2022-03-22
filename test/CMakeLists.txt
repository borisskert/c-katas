file(GLOB_RECURSE SOURCES *.c)

add_executable(c_katas_test ${SOURCES})

target_link_libraries (c_katas_test PRIVATE c_katas_lib "${CRITERION_LIBRARIES}")

# Enable a few warnings
if (CMAKE_COMPILER_IS_GNUCC)
    target_compile_options (c_katas_test PRIVATE -Wall -Wextra)
endif (CMAKE_COMPILER_IS_GNUCC)
if (MSVC)
    target_compile_options (c_katas_test PRIVATE /W4)
endif (MSVC)

add_test (c_katas_test c_katas_test)
