#include "include/utils.hpp"

int main(void) {
  error_t error = { .error_message = ":3", .error_number = 2 };
  result_t<uint8_t> result(3);

  printf("%d", check_result<uint8_t>(result));
}