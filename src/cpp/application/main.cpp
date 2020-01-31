#include <caf/all.hpp>
#include <caf/io/all.hpp>
#include <file.hpp>
#include <hello_world.hpp>
#include <mirror.hpp>

namespace caf {
CAF_MSG_TYPE_ADD_ATOM(addition_atom);
CAF_MSG_TYPE_ADD_ATOM(subtraction_atom);
CAF_MSG_TYPE_ADD_ATOM(multiplication_atom);
CAF_MSG_TYPE_ADD_ATOM(division_atom);
} // namespace caf

using math_actor = caf::typed_actor<
  caf::replies_to<caf::addition_atom, int, int>::with<int>,
  caf::replies_to<caf::subtraction_atom, int, int>::with<int>,
  caf::replies_to<caf::multiplication_atom, int, int>::with<int>,
  caf::replies_to<caf::division_atom, int, int>::with<int>>;

math_actor::behavior_type math() {
  return {[](caf::addition_atom, int x, int y) { return x + y; },
          [](caf::subtraction_atom, int x, int y) { return x - y; },
          [](caf::multiplication_atom, int x, int y) { return x * y; },
          [](caf::division_atom, int x, int y) -> caf::result<int> {
            if (y == 0) {
              return caf::sec::invalid_argument;
            }
            return x / y;
          }};
}

void caf_main(caf::actor_system& system) {
  cp::print_version_information();

  // create a new actor that calls 'mirror()'
  auto mirror_actor = system.spawn(&cp::mirror);
  // create another actor that calls 'hello_world(mirror_actor)';
  system.spawn(&cp::hello_world, mirror_actor);

  math_actor a{system.spawn(math)};
  caf::scoped_actor self{system};
  self->request(a, caf::infinite, caf::addition_atom{}, 1, 2)
    .receive([](int z) { std::cout << "1+2=" << z << '\n'; },
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
