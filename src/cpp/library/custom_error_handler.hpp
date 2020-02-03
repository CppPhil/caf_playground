#ifndef INCG_CP_CUSTOM_ERROR_HANDLER_HPP
#define INCG_CP_CUSTOM_ERROR_HANDLER_HPP
#include "int_types.hpp" // u8
#include "typed_calculator.hpp"
#include <caf/error_category.hpp> // caf::error_category
#include <caf/typed_actor.hpp>    // caf::typed_actor

namespace cp {
// Custom error category
// enum class must be of type uint8_t
// the first value must start at 1
enum class math_error : u8 { division_by_zero = 1 };

std::string to_string(math_error x);

using divider = caf::typed_actor<
  caf::replies_to<caf::division_atom, double, double>::with<double>>;

divider::behavior_type divider_impl();
} // namespace cp

// error_category must be specialized
// A custom ID shall be used
// Warning: values 0-99 are reserved by CAF
namespace caf {
template <>
struct error_category<::cp::math_error> {
  // static constexpr u8 u8_value{101};
  using type = atom_constant<atom("math_error")>;

  static constexpr atom_value value{type::uint_value()};
};
} // namespace caf
#endif // INCG_CP_CUSTOM_ERROR_HANDLER_HPP
