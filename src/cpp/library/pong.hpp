#ifndef INCG_CP_PONG_HPP
#define INCG_CP_PONG_HPP
#include "ping_pong_atoms.hpp"
#include <caf/behavior.hpp>
#include <caf/typed_actor.hpp>

namespace cp {
using pong_actor = caf::typed_actor<
  caf::replies_to<caf::ping_atom, int>::with<caf::pong_atom, int>>;

pong_actor::behavior_type pong();
} // namespace cp
#endif // INCG_CP_PONG_HPP
