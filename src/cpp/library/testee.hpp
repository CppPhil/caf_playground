#ifndef INCG_CP_TESTEE_HPP
#define INCG_CP_TESTEE_HPP
#include <caf/all.hpp>
#include <caf/raw_event_based_actor.hpp>

struct testee_state {
  uint64_t timeout_id = 41;
};

caf::behavior
testee(caf::stateful_actor<testee_state, caf::raw_event_based_actor>* self,
       caf::detail::test_actor_clock* t);

#endif // INCG_CP_TESTEE_HPP
