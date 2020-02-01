#ifndef INCG_CP_CELL_HPP
#define INCG_CP_CELL_HPP
#include <caf/typed_actor.hpp> // caf::typed_actor

namespace cp {
using cell = caf::typed_actor<caf::reacts_to<caf::put_atom, int>,
                              caf::replies_to<caf::get_atom>::with<int>>;

struct cell_state {
  int value = 0;
};

cell::behavior_type type_checked_cell(cell::stateful_pointer<cell_state> self,
                                      int x0);
} // namespace cp
#endif // INCG_CP_CELL_HPP
