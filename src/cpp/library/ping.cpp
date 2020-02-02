#include "ping.hpp"
#include <caf/event_based_actor.hpp>

namespace cp {
caf::behavior ping(caf::event_based_actor* self, const caf::actor& pong_actor,
                   int n) {
  self->send(pong_actor, caf::ping_atom_v, n);
  return {[self, pong_actor](caf::pong_atom, int x) {
    if (x > 1) {
      self->send(pong_actor, caf::ping_atom_v, x - 1);
    }
  }};
}
} // namespace cp
