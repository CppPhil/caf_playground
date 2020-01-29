#include <caf.hpp>
#include <hello_world.hpp>
#include <mirror.hpp>

void caf_main(caf::actor_system& system) {
  // create a new actor that calls 'mirror()'
  auto mirror_actor = system.spawn(&cp::mirror);
  // create another actor that calls 'hello_world(mirror_actor)';
  system.spawn(&cp::hello_world, mirror_actor);
  // system will wait until both actors are destroyed before leaving main
}

// creates a main function for us that calls our caf_main
CAF_MAIN()
