#define CAF_SUITE ping_pong_test

#include <caf/actor.hpp>    // caf::actor
#include <caf/test/dsl.hpp> // test_coordinator_fixture
#include <ping.hpp>         // cp::ping
#include <pong.hpp>         // cp::pong

namespace {
struct ping_pong_fixture : test_coordinator_fixture<> {
  cp::pong_actor pong_actor;

  ping_pong_fixture() {
    // Spawn the Pong actor.
    pong_actor = sys.spawn(&cp::pong);
    // Run initialization code for Pong.
    run();
  }
};
} // anonymous namespace

CAF_TEST_FIXTURE_SCOPE(ping_pong_tests, ping_pong_fixture)

CAF_TEST(three pings) {
  // Spawn the Ping actor and run its initialization code.
  auto ping_actor = sys.spawn(&cp::ping, pong_actor, 3);
  sched.run_once();
  // Test communication between Ping and Pong
  expect((caf::ping_atom, int), from(ping_actor).to(pong_actor).with(_, 3));
  expect((caf::pong_atom, int), from(pong_actor).to(ping_actor).with(_, 3));
  expect((caf::ping_atom, int), from(ping_actor).to(pong_actor).with(_, 2));
  expect((caf::pong_atom, int), from(pong_actor).to(ping_actor).with(_, 2));
  expect((caf::ping_atom, int), from(ping_actor).to(pong_actor).with(_, 1));
  expect((caf::pong_atom, int), from(pong_actor).to(ping_actor).with(_, 1));
  // No further messages allowed.
  disallow((caf::ping_atom, int), from(ping_actor).to(pong_actor).with(_, 1));
}

CAF_TEST_FIXTURE_SCOPE_END()
