cmake_minimum_required(VERSION 2.8)
project(cpptest)

if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()


SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_policy(SET CMP0015 NEW)

SET(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(algo)

