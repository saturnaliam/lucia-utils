/* ============================== UTILS ============================== */
/* Common functions, headers, and types I use across multiple projects */

#ifndef UTILS_HPP
#define UTILS_HPP

// headers i usually include anyways
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <variant>
#include <string>

// int typedefs
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

// error type
struct error_t {
  std::string error_message;
  uint64_t error_number;
};

// result type
template<typename T>
using result_t = std::variant<T, error_t>;

template<typename T>
inline bool check_result(const result_t<T> &result) {
  return (std::get_if<error_t>(&result) != nullptr);
}

#endif