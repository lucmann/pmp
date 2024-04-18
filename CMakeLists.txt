cmake_minimum_required(VERSION 3.12)

set(PROJECT_VERSION "0.1.0")
project(PMP VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

option(PMP_BUILD_RUST "Enable building of Rust practices" OFF)

if (PMP_BUILD_RUST)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/CMakeRust/cmake")
    enable_language(Rust)
    include(CMakeCargo)

    if (CMAKE_Rust_COMPILER)
        add_subdirectory(rust)
    else()
        message(WARNING "Not found Rust compiler")
    endif()
endif()

if (CMAKE_C_COMPILER)
    add_subdirectory(c)
endif()

if (CMAKE_CXX_COMPILER)
    add_subdirectory(cxx)
endif()

