set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(example main.cpp)
target_link_libraries(example PRIVATE meta-funcs)

#target_compile_options(example PRIVATE
#  -freflection
#)