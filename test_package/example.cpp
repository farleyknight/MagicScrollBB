#include "MagicScrollBB.hpp"

using Buffer = MagicScrollBB;

int main() {
  auto buffer = MagicScrollBB(1024);
  buffer.write_string(0, "Hello, world!");
  auto value = buffer.read_string(0);
  printf("%s", value.c_str());
}
