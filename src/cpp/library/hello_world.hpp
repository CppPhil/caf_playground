#ifndef INCG_CP_HELLO_WORLD_HPP
#define INCG_CP_HELLO_WORLD_HPP
#include "CAF_INCLUDES_BEGIN"
#include "CAF_INCLUDES_END"
#include <caf/all.hpp>

namespace cp {
void hello_world(caf::event_based_actor* self, const caf::actor& buddy);
} // namespace cp

#endif // INCG_CP_HELLO_WORLD_HPP
