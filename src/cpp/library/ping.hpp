#ifndef INCG_CP_PING_HPP
#define INCG_CP_PING_HPP
#include "pong.hpp" // cp::pong_actor
#include <caf/behavior.hpp>
#include <caf/typed_actor.hpp>

namespace cp {
using ping_actor = caf::typed_actor<caf::reacts_to<caf::pong_atom, int>>;

ping_actor::behavior_type ping(ping_actor::pointer self,
                               const pong_actor& pong_actor, int n);
} // namespace cp
#endif // INCG_CP_PING_HPP
