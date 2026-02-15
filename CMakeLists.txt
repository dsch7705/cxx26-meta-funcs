cmake_minimum_required(VERSION 4.0)
project(refl-test)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(meta-funcs INTERFACE)
target_include_directories(meta-funcs INTERFACE include)
target_compile_options(meta-funcs INTERFACE
  -freflection
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH CLANG_BIN_DIR)
  cmake_path(GET CLANG_BIN_DIR PARENT_PATH CLANG_DIR)
  
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -print-target-triple
    OUTPUT_VARIABLE CLANG_TARGET_TRIPLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  set(CLANG_STDLIB_DIR ${CLANG_DIR}/lib/${CLANG_TARGET_TRIPLE})

  target_include_directories(meta-funcs INTERFACE 
    ${CLANG_DIR}/lib/clang/21/include
    ${CLANG_DIR}/include/c++/v1
    ${CLANG_DIR}/include/${CLANG_TARGET_TRIPLE}/c++/v1
  )

  target_compile_options(meta-funcs INTERFACE 
    -nostdinc++
    -fexpansion-statements
    -fannotation-attributes
  )

  target_link_libraries(meta-funcs INTERFACE
    ${CLANG_STDLIB_DIR}/libc++.a
    ${CLANG_STDLIB_DIR}/libc++abi.a
  )
endif()

add_subdirectory(example)