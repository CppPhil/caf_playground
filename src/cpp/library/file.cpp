#include "file.hpp"
#include "version.hpp"
#include <cinttypes>
#include <cstdio>  // std::printf
#include <cstring> // std::strlen

namespace cp {
extern "C" int print(const char* txt) {
  std::printf("Output: \"%s\"\n", txt);
  return static_cast<int>(std::strlen(txt));
}

int print_version_information() {
  return std::printf("VERSION  = %s\n"
                     "MAJOR    = %" PRIu32 "\n"
                     "MINOR    = %" PRIu32 "\n"
                     "PATCH    = %" PRIu32 "\n"
                     "TWEAK    = %" PRIu32 "\n"
                     "GIT HASH = %s\n",
                     version.data(), version_major, version_minor,
                     version_patch, version_tweak, git_hash.data());
}
} // namespace cp
