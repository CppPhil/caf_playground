#ifndef INCG_CP_PING_HPP
#define INCG_CP_PING_HPP
#include <caf/behavior.hpp>

namespace cp {
caf::behavior ping(caf::event_based_actor* self, const caf::actor& pong_actor,
                   int n);
} // namespace cp
#endif // INCG_CP_PING_HPP
