#include "delegation.hpp"
#include "aprintf.hpp"
#include <caf/all.hpp>
#include <caf/event_based_actor.hpp> // caf::event_based_actor
#include <pl/current_function.hpp>   // PL_CURRENT_FUNCTION

namespace cp {
using namespace std::chrono_literals;

void actor_a(caf::event_based_actor* self, const calc& worker) {
  self->request(worker, 10s, caf::addition_atom::value, 1, 2)
    .then([self](int result) {
      aprintf(self, "{}: 1 + 2 = {}\n", PL_CURRENT_FUNCTION, result);
    });
}

calc::behavior_type actor_b(calc::pointer self, const calc& worker) {
  return {[self, worker](caf::addition_atom add, int x, int y) {
            return self->delegate(worker, add, x, y);
          },
          [self, worker](caf::subtraction_atom subtract, int x, int y) {
            return self->delegate(worker, subtract, x, y);
          },
          [self, worker](caf::multiplication_atom mul, int x, int y) {
            return self->delegate(worker, mul, x, y);
          },
          [self, worker](caf::division_atom div, int x, int y) {
            return self->delegate(worker, div, x, y);
          }};
}

calc::behavior_type actor_c() {
  return {[](caf::addition_atom, int x, int y) { return x + y; },
          [](caf::subtraction_atom, int x, int y) { return x - y; },
          [](caf::multiplication_atom, int x, int y) { return x * y; },
          [](caf::division_atom, int x, int y) -> caf::result<int> {
            if (y == 0) {
              return caf::sec::invalid_argument;
            }

            return x / y;
          }};
}

void launch_delegation_example(caf::actor_system& system) {
  system.spawn(&actor_a, system.spawn(&actor_b, system.spawn(&actor_c)));
}
} // namespace cp
