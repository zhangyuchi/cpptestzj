cmake_minimum_required(VERSION 2.8)
project(cpptest)

if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()


SET(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_policy(SET CMP0015 NEW)

SET(CMAKE_VERBOSE_MAKEFILE on)

SET(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations -Wall -std=c++11 -Wextra -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -Wno-parentheses -fmerge-all-constants -g3")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

AUX_SOURCE_DIRECTORY(algo ALGOSRCS)


ADD_EXECUTABLE(algo ${ALGOSRCS})
