#ifndef INCG_CP_COMPOSABLE_BEHAVIOR_HPP
#define INCG_CP_COMPOSABLE_BEHAVIOR_HPP
#include "typed_calculator.hpp"
#include <caf/composable_behavior.hpp> // caf::composable_behavior
#include <caf/composed_behavior.hpp>   // caf::composed_behavior
#include <caf/typed_actor.hpp>         // caf::typed_actor

namespace cp {
using adder = caf::typed_actor<
  caf::replies_to<caf::add_atom, int, int>::with<int>>;

using multiplier = caf::typed_actor<
  caf::replies_to<caf::multiplication_atom, int, int>::with<int>>;

class adder_bhvr : public caf::composable_behavior<adder> {
public:
  caf::result<int> operator()(caf::add_atom, int x, int y) override;
};

class multiplier_bhvr : public caf::composable_behavior<multiplier> {
public:
  caf::result<int> operator()(caf::multiplication_atom, int x, int y) override;
};

// calculator_bhvr can be inherited from or composed further
using calculator_bhvr = caf::composed_behavior<adder_bhvr, multiplier_bhvr>;
} // namespace cp
#endif // INCG_CP_COMPOSABLE_BEHAVIOR_HPP
