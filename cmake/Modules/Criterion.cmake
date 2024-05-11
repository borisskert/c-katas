include(ExternalProject)
ExternalProject_Add(
        Criterion
        GIT_REPOSITORY https://github.com/Snaipe/Criterion.git
        GIT_TAG v2.4.2
        SOURCE_DIR ${CMAKE_BINARY_DIR}/Criterion-src
        BUILD_IN_SOURCE TRUE
        CONFIGURE_COMMAND ""
        BUILD_COMMAND meson build
        COMMAND ninja -C build
        INSTALL_COMMAND cp -r ${CMAKE_BINARY_DIR}/Criterion-src/build/src ${CMAKE_BINARY_DIR}/Criterion
)

ExternalProject_Get_Property(Criterion SOURCE_DIR)
set(Criterion_SRC_DIR ${SOURCE_DIR})
