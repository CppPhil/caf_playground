#include "composable_behavior.hpp"

namespace cp {
caf::result<int> adder_bhvr::operator()(caf::add_atom, int x, int y) {
  return x + y;
}

caf::result<int> multiplier_bhvr::operator()(caf::multiplication_atom, int x,
                                             int y) {
  return x * y;
}
} // namespace cp
