#include "testee.hpp"
#include <chrono>

using namespace caf;
using namespace std::literals::chrono_literals;

behavior testee(stateful_actor<testee_state, raw_event_based_actor>* self,
                detail::test_actor_clock* t) {
  return {
    [=](ok_atom) {
      auto n = t->now() + 10s;
      self->state.timeout_id += 1;
      t->set_ordinary_timeout(n, self, "", self->state.timeout_id);
    },
    [=](add_atom) {
      auto n = t->now() + 10s;
      self->state.timeout_id += 1;
      t->set_multi_timeout(n, self, "", self->state.timeout_id);
    },
    [=](put_atom) {
      auto n = t->now() + 10s;
      self->state.timeout_id += 1;
      auto mid = make_message_id(self->state.timeout_id).response_id();
      t->set_request_timeout(n, self, mid);
    },
    [](const timeout_msg&) {
      // nop
    },
    [](const error&) {
      // nop
    },
    [](const std::string&) {
      // nop
    },
    [=](group& grp) { self->join(grp); },
    [=](exit_msg& x) { self->quit(x.reason); },
  };
}
