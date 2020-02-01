#ifndef INCG_CP_DICTIONARY_HPP
#define INCG_CP_DICTIONARY_HPP
#include <caf/composable_behavior.hpp> // caf::composable_behavior
#include <caf/typed_actor.hpp>         // caf::typed_actor
#include <string>                      // std::string
#include <unordered_map>               // std::unordered_map

namespace cp {
using dict = caf::typed_actor<
  caf::reacts_to<caf::put_atom, std::string, std::string>,
  caf::replies_to<caf::get_atom, std::string>::with<std::string>>;

class dict_behavior : public caf::composable_behavior<dict> {
public:
  caf::result<std::string> operator()(caf::get_atom,
                                      caf::param<std::string> key) override;

  caf::result<void> operator()(caf::put_atom, caf::param<std::string> key,
                               caf::param<std::string> value) override;

protected:
  std::unordered_map<std::string, std::string> m_values;
};
} // namespace cp
#endif // INCG_CP_DICTIONARY_HPP
