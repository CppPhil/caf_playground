#include "test.hpp"
#include <cstdio>

namespace cp {
namespace test {
void runTest()
{
    std::puts("runTest()");
}
} // namespace test
} // namespace cp

int main()
{
    std::puts("Test main here.");
    cp::test::runTest();
}

