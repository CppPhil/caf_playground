#include "custom_message_type.hpp"
#include "aprintf.hpp"
#include <caf/event_based_actor.hpp>
#include <caf/typed_actor.hpp>
#include <caf/typed_event_based_actor.hpp>
#include <pl/algo/ranged_algorithms.hpp> // pl::algo::transform

namespace caf {
using process_atom = atom_constant<atom("process")>;
} // namespace caf

namespace cp {
namespace {
using actor1 = caf::typed_actor<
  caf::replies_to<caf::process_atom, foo>::with<foo>>;

actor1::behavior_type first_actor() {
  return {[](caf::process_atom, foo foo) {
    const int factor{foo.b + 30};
    foo.b = factor;
    pl::algo::transform(foo.a, foo.a.begin(),
                        [factor](int value) { return value * factor; });
    return foo;
  }};
}

void buddy(caf::event_based_actor* self, const actor1& actor_1) {
  self
    ->request(actor_1, caf::infinite, caf::process_atom::value,
              foo{{1, 2, 3, 4, 5}, 3})
    .then([self](const foo& result) {
      cp::aprintf(self, "custom_message_type_result: {}\n", result);
    });
}
} // anonymous namespace

void launch_custom_message_type_example(caf::actor_system& system) {
  system.spawn(&buddy, system.spawn(&first_actor));
}
} // namespace cp
