#define CAF_SUITE test
#include <caf/optional.hpp>
#include <caf/test/unit_test.hpp>

using namespace caf;

namespace {

struct qwertz {
  qwertz(int x, int y) : x_(x), y_(y) {
    // nop
  }
  int x_;
  int y_;
};

bool operator==(const qwertz& lhs, const qwertz& rhs) {
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}

} // namespace

CAF_TEST(empty) {
  optional<int> x;
  optional<int> y;
  CAF_CHECK(x == y);
  CAF_CHECK(!(x != y));
}

CAF_TEST(equality) {
  optional<int> x = 42;
  optional<int> y = 7;
  CAF_CHECK(x != y);
  CAF_CHECK(!(x == y));
}

CAF_TEST(ordering) {
  optional<int> x = 42;
  optional<int> y = 7;
  CAF_CHECK(x > y);
  CAF_CHECK(x >= y);
  CAF_CHECK(y < x);
  CAF_CHECK(y <= x);
  CAF_CHECK(!(y > x));
  CAF_CHECK(!(y >= x));
  CAF_CHECK(!(x < y));
  CAF_CHECK(!(x <= y));
  CAF_CHECK(x < 4711);
  CAF_CHECK(4711 > x);
  CAF_CHECK(4711 >= x);
  CAF_CHECK(!(x > 4711));
  CAF_CHECK(!(x >= 4711));
  CAF_CHECK(!(4211 < x));
  CAF_CHECK(!(4211 <= x));
}

CAF_TEST(custom_type_none) {
  optional<qwertz> x;
  CAF_CHECK(x == none);
}

CAF_TEST(custom_type_engaged) {
  qwertz obj{1, 2};
  optional<qwertz> x = obj;
  CAF_CHECK(x != none);
  CAF_CHECK(obj == x);
  CAF_CHECK(x == obj);
  CAF_CHECK(obj == *x);
  CAF_CHECK(*x == obj);
}
