#include "custom_error_handler.hpp"
#include <cmath> // std::fpclassify

namespace cp {
std::string to_string(math_error x) {
  switch (x) {
    case math_error::division_by_zero:
      return "division_by_zero";
    default:
      return "-unknown-error";
  }
}

divider::behavior_type divider_impl() {
  return {[](caf::division_atom, double x, double y) -> caf::result<double> {
    if (std::fpclassify(y) == FP_ZERO) {
      return caf::error(static_cast<u8>(math_error::division_by_zero),
                        caf::sys_atom::value);
    }
    return x / y;
  }};
}
} // namespace cp
