#include "hello_world.hpp"
#include "aprintf.hpp"
#include <chrono>
#include <string>

namespace cp {
void hello_world(caf::event_based_actor* self, const caf::actor& buddy) {
  // send "Hello World!" to our buddy ...
  self->request(buddy, std::chrono::seconds(10), "Hello World!")
    .then(
      // ... wait up to 10s for a response ...
      [=](const std::string& what) {
        // ... and print it
        aprintf(self, "{}\n", what);
      });
}
} // namespace cp
