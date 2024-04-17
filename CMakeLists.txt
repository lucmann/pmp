cmake_minimum_required(VERSION 3.12)

set(PROJECT_VERSION "0.1.0")
project(PMP VERSION ${PROJECT_VERSION})

if (CMAKE_C_COMPILER)
    add_subdirectory(c)
endif()

if (CMAKE_CXX_COMPILER)
    add_subdirectory(cxx)
endif()

if (CMAKE_Rust_COMPILER)
    add_subdirectory(rust)
endif()

