#include <aprintf.hpp>
#include <caf/all.hpp>
#include <caf/io/all.hpp>
#include <caf/io/publish.hpp>
#include <caf/io/remote_actor.hpp>
#include <cell.hpp>
#include <composable_behavior.hpp>
#include <custom_error_handler.hpp>
#include <custom_message_type.hpp>
#include <delegation.hpp>
#include <dictionary.hpp>
#include <file.hpp>
#include <hello_world.hpp>
#include <hostname.hpp>
#include <mirror.hpp>
#include <pl/algo/ranged_algorithms.hpp>
#include <pl/current_function.hpp>
#include <pl/source_line.hpp>
#include <response_promise.hpp>
#include <typed_calculator.hpp>

void typed_cell_buddy_actor_fun(caf::event_based_actor* self,
                                const cp::cell& buddy) {
  self->request(buddy, caf::infinite, caf::put_atom{}, 55);

  self->request(buddy, caf::infinite, caf::get_atom{}).then([self](int result) {
    cp::aprintf(self, "{}:{}\n", PL_CURRENT_FUNCTION, result);
  });
}

// Utility function to print an exit message with custom name.
void print_on_exit(const caf::actor& hdl, const std::string& name) {
  hdl->attach_functor([name](const caf::error& reason) {
    std::printf("%s exited: %s\n", name.c_str(),
                caf::to_string(reason).c_str());
  });
}

void waiting_testee(caf::event_based_actor* self,
                    const std::vector<cp::cell>& cells) {
  for (auto& x : cells) {
    self->request(x, std::chrono::seconds(1), caf::get_atom::value)
      .await(
        [self, x](int y) { cp::aprintf(self, "cell #{} -> {}\n", x.id(), y); });
  }
}

void multiplexed_testee(caf::event_based_actor* self,
                        const std::vector<cp::cell>& cells) {
  for (auto& x : cells) {
    self->request(x, std::chrono::seconds(1), caf::get_atom::value)
      .then([self, x](int y) {
        cp::aprintf(self, "cell # {} -> {}\n", x.id(), y);
      });
  }
}

void blocking_testee(caf::blocking_actor* self,
                     const std::vector<cp::cell>& cells) {
  for (auto& x : cells) {
    self->request(x, std::chrono::seconds(1), caf::get_atom::value)
      .receive([&self, &x](
                 int y) { cp::aprintf(self, "cell #{} -> {}\n", x.id(), y); },
               [&self, &x](caf::error& err) {
                 cp::aprintf(self, "cell #{} -> {}\n", x.id(),
                             self->system().render(err));
               });
  }
}

caf::behavior test_actor_function() {
  return {[](std::string s) {
    pl::algo::transform(s, s.begin(), [](char c) {
      const unsigned char res{static_cast<unsigned char>(c)};
      return res
             & ~0b0010'0000U; // Uppercase it by turning the 3rd highest bit off
    });
    return s;
  }};
}

void test_actor_buddy_function(caf::event_based_actor* self,
                               const caf::actor& buddy) {
  using namespace std::string_literals;
  self->request(buddy, caf::infinite, "HiTheRe"s)
    .then([self](const std::string& result_string) {
      cp::aprintf(self,
                  "test_actor_buddy_function: Got \"{}\" from remote actor\n",
                  result_string);
    });
}

class config : public caf::actor_system_config {
public:
  config() {
    /*
      add_error_category<cp::math_error>(
      caf::error_category<cp::math_error>::value);
    */
    add_message_type<cp::foo>("foo");
  }
};

void caf_main(caf::actor_system& system, [[maybe_unused]] const config& cfg) {
  cp::print_version_information();

  auto mirror_actor = system.spawn(&cp::mirror);
  system.spawn(&cp::hello_world, mirror_actor);
  print_on_exit(mirror_actor, "MIRROR ACTOR");

  auto typed_calculator_actor = system.spawn<cp::typed_calculator>();
  caf::scoped_actor self{system};
  self
    ->request(typed_calculator_actor, caf::infinite, caf::addition_atom{}, 1, 2)
    .receive([self = self.ptr()](int z) { cp::aprintf(self, "1+2={}\n", z); },
             [self = self.ptr(), &system](caf::error& err) {
               cp::aprintf(self, "Error: {}\n", system.render(err));
             });

  auto cell = system.spawn(&cp::type_checked_cell, 0);
  auto cell_buddy = system.spawn(&typed_cell_buddy_actor_fun, cell);

  auto f = caf::make_function_view(system.spawn<cp::calculator_bhvr>());
  cp::aprintf(self, "10 + 20 = {}\n7 * 9 = {}\n",
              f(caf::add_atom::value, 10, 20),
              f(caf::multiplication_atom::value, 7, 9));

  auto dict_functor = caf::make_function_view(
    system.spawn<cp::dict_behavior>());
  dict_functor(caf::put_atom::value, "#1", "Hello CAF!");
  cp::aprintf(self, "get {}\n", dict_functor(caf::get_atom::value, "#1"));

  // Cells example
  std::vector<cp::cell> cells{};
  for (int i{0}; i < 5; ++i) {
    cells.push_back(system.spawn(&cp::type_checked_cell, i * i));
  }
  system.spawn(&waiting_testee, cells);     // LIFO order
  system.spawn(&multiplexed_testee, cells); // arbitrary order
  blocking_testee(self.ptr(), cells);       // FIFO order

  auto div = system.spawn(&cp::divider_impl);
  const double x{7.0}, y{0.0};
  self->request(div, std::chrono::seconds{10}, caf::division_atom::value, x, y)
    .receive([&self, x,
              y](double z) { cp::aprintf(self, "{} / {} = {}\n", x, y, z); },
             [&self, &system, x, y](const caf::error& err) {
               cp::aprintf(self, "*** cannot compute {} / {} => {}\n", x, y,
                           system.render(err));
             });

  // Delegation example
  cp::launch_delegation_example(system);

  // Response promise example
  cp::launch_response_promise_example(system);

  // Custom message type example
  cp::launch_custom_message_type_example(system);

  // node A
  constexpr u16 port{4242};
  auto test_actor = system.spawn(test_actor_function);
  const caf::expected<u16> result{caf::io::publish(test_actor, port)};
  cp::aprintf(self, "{}, {} result: {}\n", PL_CURRENT_FUNCTION, PL_SOURCE_LINE,
              result);

  // node B
  cp::hostname().map([&system, &self](const std::string& hostname) {
    cp::aprintf(self, "hostname: {}\n", hostname);
    caf::expected<caf::actor> expected_node{
      caf::io::remote_actor(system, hostname, port)};

    if (not expected_node) {
      cp::aprintf(self, "unable to connect to node A: {}\n",
                  system.render(expected_node.error()));
    } else {
      system.spawn(test_actor_buddy_function, *expected_node);
    }
  });
}

// creates a main function for us that calls our caf_main
CAF_MAIN(caf::io::middleman)
