cmake_minimum_required(VERSION 4.0)
project(refl-test)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(meta-funcs INTERFACE)
target_include_directories(meta-funcs INTERFACE include)
target_compile_options(meta-funcs INTERFACE
  -freflection
)

add_subdirectory(example)