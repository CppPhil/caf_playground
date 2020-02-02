#ifndef INCG_CP_APRINTF_HPP
#define INCG_CP_APRINTF_HPP
#include <caf/actor_ostream.hpp> // caf::actor_ostream
#include <fmt/format.h>          // fmt::format
#include <utility>               // std::forward

namespace cp {
template <typename FormatString, typename... Args>
caf::actor_ostream aprintf(caf::local_actor* self,
                           const FormatString& format_string, Args&&... args) {
  return caf::aout(self) << fmt::format(format_string,
                                        std::forward<Args>(args)...);
}

template <typename FormatString, typename... Args>
caf::actor_ostream aprintf(caf::scoped_actor& self,
                           const FormatString& format_string, Args&&... args) {
  return caf::aout(self) << fmt::format(format_string,
                                        std::forward<Args>(args)...);
}
} // namespace cp

namespace fmt {
template <typename T>
struct formatter<::caf::expected<T>> {
  constexpr auto parse(format_parse_context& ctx) {
    auto it{ctx.begin()};

    if (*it != '}') {
      throw format_error("invalid format");
    }

    return ++it;
  }

  template <typename FormatContext>
  auto format(const ::caf::expected<T>& expected, FormatContext& ctx) {
    if (expected.engaged()) {
      return format_to(ctx.out(), "{}", *expected);
    }

    return format_to(ctx.out(), "{}", ::caf::to_string(expected.error()));
  }
};
} // namespace fmt
#endif // INCG_CP_APRINTF_HPP
