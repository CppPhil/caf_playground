#include <caf/all.hpp>
#include <caf/io/all.hpp>
#include <cell.hpp>
#include <composable_behavior.hpp>
#include <custom_error_handler.hpp>
#include <delegation.hpp>
#include <dictionary.hpp>
#include <file.hpp>
#include <hello_world.hpp>
#include <mirror.hpp>
#include <pl/current_function.hpp>
#include <response_promise.hpp>
#include <typed_calculator.hpp>

void typed_cell_buddy_actor_fun(caf::event_based_actor* self,
                                const cp::cell& buddy) {
  self->request(buddy, caf::infinite, caf::put_atom{}, 55);

  self->request(buddy, caf::infinite, caf::get_atom{}).then([self](int result) {
    caf::aout(self) << PL_CURRENT_FUNCTION << ": " << result << "\n";
  });
}

// Utility function to print an exit message with custom name.
void print_on_exit(const caf::actor& hdl, const std::string& name) {
  hdl->attach_functor([name](const caf::error& reason) {
    std::printf("%s exited: %s\n", name.c_str(),
                caf::to_string(reason).c_str());
  });
}

void waiting_testee(caf::event_based_actor* self, std::vector<cp::cell> cells) {
  for (auto& x : cells) {
    self->request(x, std::chrono::seconds(1), caf::get_atom_v)
      .await([self, x](int y) {
        caf::aout(self) << "cell #" << x.id() << " -> " << y << std::endl;
      });
  }
}

void multiplexed_testee(caf::event_based_actor* self,
                        std::vector<cp::cell> cells) {
  for (auto& x : cells) {
    self->request(x, std::chrono::seconds(1), caf::get_atom_v)
      .then([self, x](int y) {
        caf::aout(self) << "cell #" << x.id() << " -> " << y << std::endl;
      });
  }
}

void blocking_testee(caf::blocking_actor* self, std::vector<cp::cell> cells) {
  for (auto& x : cells) {
    self->request(x, std::chrono::seconds(1), caf::get_atom_v)
      .receive(
        [&self, &x](int y) {
          caf::aout(self) << "cell #" << x.id() << " -> " << y << std::endl;
        },
        [&self, &x](caf::error& err) {
          caf::aout(self) << "cell #" << x.id() << " -> "
                          << self->system().render(err) << std::endl;
        });
  }
}

void caf_main(caf::actor_system& system) {
  cp::print_version_information();

  auto mirror_actor = system.spawn(&cp::mirror);
  system.spawn(&cp::hello_world, mirror_actor);
  print_on_exit(mirror_actor, "MIRROR ACTOR");

  auto typed_calculator_actor = system.spawn<cp::typed_calculator>();
  caf::scoped_actor self{system};
  self
    ->request(typed_calculator_actor, caf::infinite, caf::addition_atom{}, 1, 2)
    .receive([](int z) { std::cout << "1+2=" << z << '\n'; },
             [&system](caf::error& err) {
               std::cout << "Error: " << system.render(err) << '\n';
             });

  auto cell = system.spawn(&cp::type_checked_cell, 0);
  auto cell_buddy = system.spawn(&typed_cell_buddy_actor_fun, cell);

  auto f = caf::make_function_view(system.spawn<cp::calculator_bhvr>());
  caf::aout(self) << "10 + 20 = " << f(caf::add_atom_v, 10, 20) << "\n"
                  << "7 * 9 = " << f(caf::mul_atom_v, 7, 9) << std::endl;

  auto dict_functor
    = caf::make_function_view(system.spawn<cp::dict_behavior>());
  dict_functor(caf::put_atom_v, "#1", "Hello CAF!");
  caf::aout(self) << "get: " << dict_functor(caf::get_atom_v, "#1");

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
  self->request(div, std::chrono::seconds{10}, caf::div_atom_v, x, y)
    .receive(
      [&self, x, y](double z) {
        caf::aout(self) << x << " / " << y << " = " << z << std::endl;
      },
      [&self, x, y](const caf::error& err) {
        caf::aout(self) << "*** cannot compute " << x << " / " << y << " => "
                        << err.context() << std::endl;
      });

  // Delegation example
  cp::launch_delegation_example(system);

  // Response promise example
  cp::launch_response_promise_example(system);
}

struct foo {
  std::vector<int> a;
  int b;
};

template <typename Inspector>
typename Inspector::result_type inspect(Inspector& f, foo& x) {
  return f(caf::meta::type_name("foo"), x.a, x.b);
}

// creates a main function for us that calls our caf_main
CAF_MAIN()
