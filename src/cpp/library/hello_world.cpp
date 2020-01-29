#include "hello_world.hpp"
#include <chrono>
#include <ostream>
#include <string>

namespace cp {
void hello_world(caf::event_based_actor* self, const caf::actor& buddy) {
  // send "Hello World!" to our buddy ...
  self->request(buddy, std::chrono::seconds(10), "Hello World!")
    .then(
      // ... wait up to 10s for a response ...
      [=](const std::string& what) {
        // ... and print it
        caf::aout(self) << what << std::endl;
      });
}
} // namespace cp
