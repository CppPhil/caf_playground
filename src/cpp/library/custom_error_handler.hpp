#ifndef INCG_CP_CUSTOM_ERROR_HANDLER_HPP
#define INCG_CP_CUSTOM_ERROR_HANDLER_HPP
#include "int_types.hpp"          // u8
#include <caf/error_category.hpp> // caf::error_category
#include <caf/typed_actor.hpp>    // caf::typed_actor

namespace cp {
enum class math_error : u8 { division_by_zero = 1 };

using divider = caf::typed_actor<
  caf::replies_to<caf::div_atom, double, double>::with<double>>;

divider::behavior_type divider_impl();
} // namespace cp

namespace caf {
template <>
struct error_category<::cp::math_error> {
  static constexpr u8 value{25};
};
} // namespace caf
#endif // INCG_CP_CUSTOM_ERROR_HANDLER_HPP
