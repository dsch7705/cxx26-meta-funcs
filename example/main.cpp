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