#ifndef INCG_CP_HOSTNAME_HPP
#define INCG_CP_HOSTNAME_HPP
#include <string>          // std::string
#include <tl/optional.hpp> // tl::optional

namespace cp {
[[nodiscard]] tl::optional<std::string> hostname();
} // namespace cp
#endif // INCG_CP_HOSTNAME_HPP
