cmake_minimum_required(VERSION 3.1)

# Compiler id for Apple Clang is now AppleClang.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif()

project(cpptestzj)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/CMake
)

include(GNUInstallDirs)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

# include current path
list(APPEND ABSL_COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(ABSL_USING_CLANG ON)
else()
  set(ABSL_USING_CLANG OFF)
endif()

## pthread
find_package(Threads REQUIRED)
include_directories(.)
add_executable (functiontest ConsoleApplication11.cpp)
