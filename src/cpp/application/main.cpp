#include <caf/all.hpp>
#include <caf/io/all.hpp>
#include <cell.hpp>
#include <file.hpp>
#include <hello_world.hpp>
#include <mirror.hpp>
#include <pl/current_function.hpp>
#include <typed_calculator.hpp>

void typed_cell_buddy_actor_fun(caf::event_based_actor* self,
                                const cp::cell& buddy) {
  self->request(buddy, caf::infinite, caf::put_atom{}, 55);

  self->request(buddy, caf::infinite, caf::get_atom{}).then([self](int result) {
    caf::aout(self) << PL_CURRENT_FUNCTION << ": " << result << "\n";
  });
}

void caf_main(caf::actor_system& system) {
  cp::print_version_information();

  auto mirror_actor = system.spawn(&cp::mirror);
  system.spawn(&cp::hello_world, mirror_actor);

  auto typed_calculator_actor = system.spawn<cp::typed_calculator>();
  caf::scoped_actor self{system};
  self
    ->request(typed_calculator_actor, caf::infinite, caf::addition_atom{}, 1, 2)
    .receive([](int z) { std::cout << "1+2=" << z << '\n'; },
             [&system](caf::error& err) {
               std::cout << "Error: " << system.render(err) << '\n';
             });

  auto cell = system.spawn(&cp::type_checked_cell);
  auto cell_buddy = system.spawn(&typed_cell_buddy_actor_fun, cell);
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
