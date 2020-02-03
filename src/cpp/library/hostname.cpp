#include "hostname.hpp"
#include <caf/io/network/interfaces.hpp> // caf::io::network::interfaces::list_addresses

namespace cp {
[[nodiscard]] tl::optional<std::string> hostname() {
  const std::vector<std::string> addresses{
    caf::io::network::interfaces::
      list_addresses(caf::io::network::protocol::ipv4, false)};

  if (addresses.empty()) {
    return tl::nullopt;
  }

  return addresses.front();
}
} // namespace cp
