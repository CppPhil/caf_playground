#include "pong.hpp"

namespace cp {
pong_actor::behavior_type pong() {
  return {[](caf::ping_atom, int x) {
    return std::make_tuple(caf::pong_atom::value, x);
  }};
}
} // namespace cp
