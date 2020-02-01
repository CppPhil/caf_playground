#include "custom_error_handler.hpp"
#include <cmath> // std::fpclassify

namespace cp {
divider::behavior_type divider_impl() {
  return {[](caf::div_atom, double x, double y) -> caf::result<double> {
    if (std::fpclassify(y) == FP_ZERO) {
      return caf::error(math_error::division_by_zero);
    }
    return x / y;
  }};
}
} // namespace cp
