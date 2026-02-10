#pragma once

#include "meta_print.h"

// Bake member information into the structure of an incomplete type.
consteval auto bake_aggregate(std::meta::info shell, std::span<const std::meta::info> member_types, std::vector<std::string_view> member_names = {})
{
  if (is_template(shell)) {
    shell = substitute(shell, member_types);
  }

  if (is_complete_type(shell)) {
    throw_meta_exception("Cannot define an aggregate for a complete type", shell);
  }

  std::vector<std::meta::info> specs;

  unsigned int i = 0;
  unsigned int j = 0;
  for (auto t : member_types) {
    if (member_names.size() > i) {
      std::string_view name = *(member_names.begin() + (i++));
      specs.push_back(data_member_spec(t, {.name = name}));
    } else {
      std::array<char, 16> buf = {'_', 'm'};
      std::to_chars(buf.begin() + 2, buf.begin() + buf.size(), j++);
  
      specs.push_back(data_member_spec(t, {.name = buf.data()}));
    }
  }
  return define_aggregate(shell, specs);
}

// Mirror the nonstatic data members of source into shell.
consteval auto mimic_aggregate(std::meta::info shell, std::meta::info source)
{
  if (!is_aggregate_type(source)) {
    throw_meta_exception("source must be an aggregate type", source);
  }

  auto members = nonstatic_data_members_of(source, std::meta::access_context::unchecked());
  std::vector<std::meta::info> member_types;
  std::vector<std::string_view> member_names;

  for (auto m : members) {
    member_types.push_back(type_of(m));
    member_names.push_back(identifier_of(m));
  }

  if (is_template(shell)) {
    std::meta::info shell_sub[] {source};
    shell = substitute(shell, shell_sub);
  }
  return bake_aggregate(shell, member_types, member_names);
}

// Compose aggregates in sources into shell.
consteval auto compose_aggregate(std::meta::info shell, std::span<const std::meta::info> sources)
{
  std::vector<std::meta::info> member_types;
  std::vector<std::string_view> member_names;
  for (auto s : sources) {
    if (!is_aggregate_type(s)) {
      throw_meta_exception("source must be an aggregate type", s);
    }

    auto members = nonstatic_data_members_of(s, std::meta::access_context::unchecked());
    for (auto m : members) {
      member_types.push_back(type_of(m));
      member_names.push_back(identifier_of(m));
    }
  }

  if (is_template(shell)) {
    shell = substitute(shell, sources);
  }
  return bake_aggregate(shell, member_types, member_names);
}