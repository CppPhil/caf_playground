#ifndef INCG_CP_HOSTNAME_HPP
#define INCG_CP_HOSTNAME_HPP
#include "optional.hpp" // tl::optional
#include <string>       // std::string

namespace cp {
[[nodiscard]] tl::optional<std::string> hostname();
} // namespace cp
#endif // INCG_CP_HOSTNAME_HPP
