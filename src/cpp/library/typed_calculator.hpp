#ifndef INCG_CP_TYPED_CALCULATOR_HPP
#define INCG_CP_TYPED_CALCULATOR_HPP
#include <caf/replies_to.hpp>              // caf::replies_to
#include <caf/type_nr.hpp>                 // CAF_MSG_TYPE_ADD_ATOM
#include <caf/typed_event_based_actor.hpp> // caf::typed_event_based_actor

namespace caf {
CAF_MSG_TYPE_ADD_ATOM(addition_atom);
CAF_MSG_TYPE_ADD_ATOM(subtraction_atom);
CAF_MSG_TYPE_ADD_ATOM(multiplication_atom);
CAF_MSG_TYPE_ADD_ATOM(division_atom);
} // namespace caf

namespace cp {
using calculator_actor = caf::typed_actor<
  caf::replies_to<caf::addition_atom, int, int>::with<int>,
  caf::replies_to<caf::subtraction_atom, int, int>::with<int>,
  caf::replies_to<caf::multiplication_atom, int, int>::with<int>,
  caf::replies_to<caf::division_atom, int, int>::with<int>>;

class typed_calculator : public calculator_actor::base {
public:
  using base_type = calculator_actor::base;

  typed_calculator(caf::actor_config& cfg) : base_type{cfg} {
  }

  behavior_type make_behavior() override {
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
};
} // namespace cp
#endif // INCG_CP_TYPED_CALCULATOR_HPP
