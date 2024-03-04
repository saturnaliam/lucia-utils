/* ================================================= UTILS ================================================= */
/* Common functions, headers, and types I use across projects, especially for reverse engineering & modding. */

#ifndef UTILS_HPP
#define UTILS_HPP

// headers i usually include anyways
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <variant>
#include <optional>
#include <string>
#include "windows.hpp"

// int typedefs
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uintptr_t uptr;
typedef intptr_t sptr;

namespace utils {
  // error type
  struct error_t {
    std::string error_message;
    uint64_t error_number;
  };

  // result type
  template<typename T>
  using result_t = std::variant<T, utils::error_t>;

  inline result_t<uptr*> follow_pointer_path(const std::vector<uptr> &pointers, const uptr &base_address) {
    uptr temp = base_address;

    for (size_t i = 0; i < pointers.size() - 1; i++) {
      temp = *reinterpret_cast<uptr*>(temp + pointers[i]);
    }

    uptr *final = reinterpret_cast<uptr*>(temp + pointers.back());

    if (final == nullptr) {
      return (utils::error_t){ .error_message = "Null address!", .error_number = 1 };
    } else {
      return final;
    }
  }
}

template<typename T>
inline bool check_result(const utils::result_t<T> result) {
  return (std::get_if<utils::error_t>(&result) != nullptr);
}

template<typename T>
inline std::optional<T> get_result(const utils::result_t<T> &result) {
  return check_result<T>(&result) ? std::optional<T>{std::get<T>(result)} : std::nullopt;
}

#endif
