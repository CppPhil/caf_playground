#include "mirror.hpp"
#include "aprintf.hpp"
#include <pl/string_view.hpp>
#include <string>

namespace cp {
caf::behavior mirror(caf::event_based_actor* self) {
  // return the (initial) actor behavior
  return {// a handler for messages containing a single string
          // that replies with a string
          [=](const std::string& what) -> std::string {
            aprintf(self, "{}\n", what);

            const pl::string_view sv{what};

            // reply "!dlroW olleH"
            return std::string(sv.rbegin(), sv.rend());
          }};
}
} // namespace cp
