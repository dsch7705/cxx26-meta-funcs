# C++26 Meta Functions

## Features
- Programmatically define aggregate types
- Iterate over and print the members of a type

## Prerequisites
- CMake 4.0+
- One of the following compilers:
  - GCC 16+
  - Bloomberg's P2996 Clang fork

## Example
### main.cpp
```c++
#include "meta_aggregate.h"
#include "meta_print.h"

template <typename... Ts>
struct Shell;

consteval {
  auto baked1 = bake_aggregate(^^Shell, {^^int, ^^float}, {"one", "two"});
  auto baked2 = bake_aggregate(^^Shell, {^^double, ^^char}, {"three", "four"});

  auto composed = compose_aggregate(^^Shell<int>, {baked1, baked2});

  mimic_aggregate(^^Shell<>, composed);
}

int main()
{
  print_nonstatic_data_members_of<Shell<int>>();
  std::println();
  print_nonstatic_data_members_of<Shell<>>();
}
```
### Output
```
int Shell<int>::one
float Shell<int>::two
double Shell<int>::three
char Shell<int>::four

int Shell<>::one
float Shell<>::two
double Shell<>::three
char Shell<>::four
```
### Building the example
```shell
git clone https://github.com/dsch7705/cxx26-meta-funcs.git
cd cxx26-meta-funcs

mkdir build && cd build

cmake -DCMAKE_C_COMPILER=/path/to/c/compiler -DCMAKE_CXX_COMPILER=/path/to/cxx/compiler ..
cmake --build .
```