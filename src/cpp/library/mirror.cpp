#include "mirror.hpp"
#include "file.hpp"
#include <ostream>
#include <pl/string_view.hpp>
#include <string>

namespace cp {
caf::behavior mirror(caf::event_based_actor* self) {
  // return the (initial) actor behavior
  return {// a handler for messages containing a single string
          // that replies with a string
          [=](const std::string& what) -> std::string {
            // prints "Hello World!" via aout (thread-safe cout wrapper)
            caf::aout(self) << what << std::endl;
            cp::print(what.c_str());

            const pl::string_view sv{what};

            // reply "!dlroW olleH"
            return std::string(sv.rbegin(), sv.rend());
          }};
}
} // namespace cp
