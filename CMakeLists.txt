# Project
cmake_minimum_required(VERSION 3.16)
project(mille_converter 
    VERSION 1.0.0
    DESCRIPTION "FASER alignment data converter to Millepede-II format"
    LANGUAGES CXX
)

# Install prefix
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "Install prefix" FORCE)
    message(STATUS "Using default install prefix: ${CMAKE_INSTALL_PREFIX}")
else()
    message(STATUS "Using custom install prefix: ${CMAKE_INSTALL_PREFIX}")
endif()

# Strict c++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default Build Type to "Release" if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# Find ROOT - Auto include path by components
find_package(ROOT REQUIRED COMPONENTS Core RIO Tree)

# Add argparse subdirectory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/argparse/CMakeLists.txt")
    # 禁用 argparse 的测试和示例
    set(ARGPARSE_BUILD_TESTS OFF CACHE BOOL "Disable argparse tests")
    set(ARGPARSE_BUILD_SAMPLES OFF CACHE BOOL "Disable argparse samples")
    message(STATUS "Start argparse/CMakeLists.txt")
    add_subdirectory(argparse)
    message(STATUS "Finish argparse/CMakeLists.txt")
else()
    message(FATAL_ERROR 
        "argparse subdirectory not found. Please:\n"
        "  git submodule update --init"
    )
endif()

# Executable
add_executable(convert src/main.cc src/Mille.cc)

# Add include directory
target_include_directories(convert PRIVATE include)

# Link libraries
target_link_libraries(convert PRIVATE 
    ROOT::Core 
    ROOT::RIO 
    ROOT::Tree
    argparse::argparse
)
# Compiler options based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(convert PRIVATE -g -O0 -Wall -Wextra)
else()
    target_compile_options(convert PRIVATE -O3 -DNDEBUG)
endif()

# Configuration summary
message(STATUS "=== Mille Converter Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "ROOT version: ${ROOT_VERSION}")
message(STATUS "argparse dir: ${CMAKE_CURRENT_SOURCE_DIR}/argparse")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "=====================================")

# Installation
install(TARGETS convert
    RUNTIME DESTINATION bin
    COMPONENT Runtime
)