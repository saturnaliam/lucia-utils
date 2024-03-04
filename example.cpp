#include "include/utils.hpp"

int main(void) {
  utils::error_t error = { .error_message = ":3", .error_number = 2 };
  utils::result_t<u8> result(error);

  printf("%d", check_result<u8>(result));
}
