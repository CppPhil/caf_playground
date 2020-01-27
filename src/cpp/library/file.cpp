#include "file.hpp"
#include <cstdio> // std::printf
#include <cstring> // std::strlen

namespace cp {
extern "C" int print(const char* txt)
{
    std::printf("Output: \"%s\"", txt);
    return static_cast<int>(std::strlen(txt));
}
} // namespace cp

