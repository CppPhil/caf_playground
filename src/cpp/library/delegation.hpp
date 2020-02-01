#ifndef INCG_CP_DELEGATION_HPP
#define INCG_CP_DELEGATION_HPP
#include "typed_calculator.hpp"

namespace cp {
using calc = calculator_actor;

void actor_a(caf::event_based_actor* self, const calc& worker);

calc::behavior_type actor_b(calc::pointer self, const calc& worker);

calc::behavior_type actor_c();

void launch_delegation_example(caf::actor_system& system);
} // namespace cp
#endif // INCG_CP_DELEGATION_HPP
