#ifndef CAFPLAYGROUND_PING_PONG_ATOMS_HPP
#define CAFPLAYGROUND_PING_PONG_ATOMS_HPP
#include <caf/atom.hpp>
namespace caf {
using pong_atom = atom_constant<atom("pong")>;
using ping_atom = atom_constant<atom("ping")>;
} // namespace caf
#endif // CAFPLAYGROUND_PING_PONG_ATOMS_HPP
