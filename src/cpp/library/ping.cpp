#include "ping.hpp"
#include <caf/typed_event_based_actor.hpp>

namespace cp {
ping_actor::behavior_type ping(ping_actor::pointer self,
                               const pong_actor& pong_actor, int n) {
  self->send(pong_actor, caf::ping_atom::value, n);
  return {[self, pong_actor](caf::pong_atom, int x) {
    if (x > 1) {
      self->send(pong_actor, caf::ping_atom::value, x - 1);
    }
  }};
}
} // namespace cp
