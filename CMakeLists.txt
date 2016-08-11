cmake_minimum_required(VERSION 3.5)
project(ClangModuleWarnings)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Weverything -Wno-pedantic -Werror -Wno-system-headers")

# When commenting out this line to disable modules, everything works as expected
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules -fcxx-modules")

add_library(mylib STATIC mylib/mylib.cpp mylib/include/mylib/mylib.h)

include_directories(SYSTEM mylib/include)

add_executable(ClangModuleWarnings main.cpp mylib)
