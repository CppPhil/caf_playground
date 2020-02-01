#include <caf/all.hpp>
#include <caf/io/all.hpp>
#include <cell.hpp>
#include <file.hpp>
#include <hello_world.hpp>
#include <mirror.hpp>
#include <typed_calculator.hpp>

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
  self->request(cell, caf::infinite, caf::put_atom{}, 50);

  self->request(cell, caf::infinite, caf::get_atom{})
    .receive([](int result) { std::cout << "Here's: " << result << '\n'; },
             [&system](caf::error& err) {
               std::cout << "Error: " << system.render(err) << '\n';
             });
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
