#include "response_promise.hpp"
#include "aprintf.hpp"
#include <caf/all.hpp>
#include <caf/replies_to.hpp>              // caf::replies_to
#include <caf/scoped_actor.hpp>            // caf::scoped_actor
#include <caf/typed_actor.hpp>             // caf::typed_actor
#include <caf/typed_event_based_actor.hpp> // caf::typed_event_based_actor

namespace cp {
namespace {
using adder
  = caf::typed_actor<caf::replies_to<caf::add_atom, int, int>::with<int>>;

// function-based, statically typed, event-based API
adder::behavior_type worker() {
  return {[](caf::add_atom, int a, int b) { return a + b; }};
}

// function-based, statically typed, event-based API
adder::behavior_type calculator_master(adder::pointer self) {
  auto w = self->spawn(worker);
  return {[self, w](caf::add_atom add_atom, int y, int z) -> caf::result<int> {
    auto rp = self->make_response_promise<int>();
    self->request(w, caf::infinite, add_atom, y, z)
      .then([rp](int result) mutable { rp.deliver(result); });
    return rp;
  }};
}
} // anonymous namespace

void launch_response_promise_example(caf::actor_system& system) {
  auto calc_actor = system.spawn(&calculator_master);

  caf::scoped_actor scoped_actor{system};

  scoped_actor->request(calc_actor, caf::infinite, caf::add_atom_v, 20, 99)
    .receive([& self = scoped_actor](
               int result) { aprintf(self, "Got: {}\n", result); },
             [& self = scoped_actor, &system](const caf::error& err) {
               aprintf(self, "Got an error: {}\n", system.render(err));
             });
}
} // namespace cp
