#ifndef INCG_CP_CUSTOM_MESSAGE_TYPE_HPP
#define INCG_CP_CUSTOM_MESSAGE_TYPE_HPP
#include <caf/actor_system.hpp>   // caf::actor_system
#include <caf/meta/type_name.hpp> // caf::meta::type_name
#include <fmt/format.h>           // fmt::formatter
#include <pl/string_view.hpp>     // pl::string_view
#include <string>                 // std::string
#include <vector>                 // std::vector

namespace cp {
struct foo {
  std::vector<int> a;
  int b;
};

template <typename Inspector>
typename Inspector::result_type inspect(Inspector& f, foo& x) {
  return f(caf::meta::type_name("foo"), x.a, x.b);
}

void launch_custom_message_type_example(caf::actor_system& system);
} // namespace cp

namespace fmt {
template <>
struct formatter<::cp::foo> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it{ctx.begin()};

    if (*it != '}') {
      throw format_error("invalid format");
    }

    return ++it;
  }

  template <typename FormatContext>
  auto format(const ::cp::foo& foo, FormatContext& ctx) {
    return format_to(ctx.out(), "foo{{a: vector{{{}}}, b: {}}}",
                     join(foo.a, ", "), foo.b);
  }

private:
  template <typename Range>
  static std::string join(const Range& range, pl::string_view delimiter) {
    std::ostringstream oss{};

    auto it = begin(range);
    const auto last = end(range);

    if (it == last) {
      return "";
    }

    const auto secondLast = std::prev(last);

    std::copy(it, secondLast,
              std::ostream_iterator<pl::meta::remove_cvref_t<decltype(*it)>>{
                oss, delimiter.data()});
    oss << *secondLast;

    return oss.str();
  }
};
} // namespace fmt
#endif // INCG_CP_CUSTOM_MESSAGE_TYPE_HPP
