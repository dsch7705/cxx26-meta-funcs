#pragma once

#include <meta>
#include <print>

template <std::meta::info R>
void print_type_of()
{
  std::println("{}", display_string_of(type_of(R)));
}

template <typename T>
void print_nonstatic_data_members_of(std::optional<T> obj = {})
{
  static constexpr auto members = define_static_array(nonstatic_data_members_of(^^T, std::meta::access_context::unchecked()));
  template for (constexpr auto m : members) {
    if (obj.has_value()) {
      const auto& obj_val = obj.value();
      std::println("{} {} = {}", display_string_of(type_of(m)), display_string_of(m), obj_val.[: m :]);
    }
    else {
      std::println("{} {}", display_string_of(type_of(m)), display_string_of(m));
    }
  }
}

template <typename T>
void print_static_data_members_of()
{
  static constexpr auto members = define_static_array(static_data_members_of(^^T, std::meta::access_context::unchecked()));
  template for (constexpr auto m : members) {
    std::println("static {} {}", display_string_of(type_of(m)), display_string_of(m));
  }
}

template <std::meta::info R>
void print_members_of()
{
  static constexpr auto members = define_static_array(members_of(R, std::meta::access_context::unchecked()));
  template for (constexpr auto m : members) {
    std::println("{}", display_string_of(m));
  }
}