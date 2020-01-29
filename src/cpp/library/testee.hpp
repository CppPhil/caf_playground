#ifndef INCG_CP_TESTEE_HPP
#define INCG_CP_TESTEE_HPP
#include "caf.hpp"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <caf/raw_event_based_actor.hpp>
#pragma GCC diagnostic pop

struct testee_state {
  uint64_t timeout_id = 41;
};

caf::behavior testee(caf::stateful_actor<testee_state, caf::raw_event_based_actor>* self,
                caf::detail::test_actor_clock* t);

#endif // INCG_CP_TESTEE_HPP

