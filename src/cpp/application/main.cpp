#include <file.hpp> // cp::print

#include <string>
#include <iostream>
#include <pl/string_view.hpp> // pl::string_view

#include "caf/all.hpp"

using std::endl;
using std::string;

using namespace caf;

behavior mirror(event_based_actor* self) {
  // return the (initial) actor behavior
  return {
    // a handler for messages containing a single string
    // that replies with a string
    [=](const string& what) -> string {
      // prints "Hello World!" via aout (thread-safe cout wrapper)
      aout(self) << what << endl;
      cp::print(what.c_str());
      
      const pl::string_view sv{what};
      
      // reply "!dlroW olleH"
      return string(sv.rbegin(), sv.rend());
    }
  };
}

void hello_world(event_based_actor* self, const actor& buddy) {
  // send "Hello World!" to our buddy ...
  self->request(buddy, std::chrono::seconds(10), "Hello World!").then(
    // ... wait up to 10s for a response ...
    [=](const string& what) {
      // ... and print it
      aout(self) << what << endl;
    }
  );
}

void caf_main(actor_system& system) {
  // create a new actor that calls 'mirror()'
  auto mirror_actor = system.spawn(mirror);
  // create another actor that calls 'hello_world(mirror_actor)';
  system.spawn(hello_world, mirror_actor);
  // system will wait until both actors are destroyed before leaving main
}

// creates a main function for us that calls our caf_main
CAF_MAIN()

