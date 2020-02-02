#include "pong.hpp"

namespace cp {
caf::behavior pong() {
  return {
    [](caf::ping_atom, int x) { return std::make_tuple(caf::pong_atom_v, x); }};
}
} // namespace cp