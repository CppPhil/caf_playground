#include "cell.hpp"
#include <caf/typed_event_based_actor.hpp> // caf::typed_event_based_actor

namespace cp {
cell::behavior_type type_checked_cell(cell::stateful_pointer<cell_state> self) {
  return {[self](caf::put_atom, int val) { self->state.value = val; },
          [self](caf::get_atom) { return self->state.value; }};
}
} // namespace cp
