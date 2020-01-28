#include <file.hpp> // cp::print
#include <iostream>
#include <pl/string_view.hpp> // pl::string_view
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include "caf/all.hpp"
#pragma GCC diagnostic pop

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

void caf_main(caf::actor_system& system) {
  // create a new actor that calls 'mirror()'
  auto mirror_actor = system.spawn(mirror);
  // create another actor that calls 'hello_world(mirror_actor)';
  system.spawn(hello_world, mirror_actor);
  // system will wait until both actors are destroyed before leaving main
}

// creates a main function for us that calls our caf_main
CAF_MAIN()
