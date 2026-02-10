# C++26 Meta Functions

## Features
- Programmatically define aggregate types
- Iterate over and print the members of a type

## Prerequisites
- GCC 16+
- CMake 4.0+

## Example
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