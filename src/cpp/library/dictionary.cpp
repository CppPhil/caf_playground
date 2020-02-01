#include "dictionary.hpp"

namespace cp {
caf::result<std::string>
dict_behavior::operator()(caf::get_atom, caf::param<std::string> key) {
  if (auto it{m_values.find(key)}; it != m_values.end()) {
    const auto& [key, value] = *it;
    (void) key;
    return value;
  }

  return "";
}

caf::result<void> dict_behavior::operator()(caf::put_atom,
                                            caf::param<std::string> key,
                                            caf::param<std::string> value) {
  if (m_values.count(key) != 0) {
    return caf::unit;
  }

  m_values.emplace(key.move(), value.move());
  return caf::unit;
}
} // namespace cp
