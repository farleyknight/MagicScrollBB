#include <fmt/core.h>
#include "MagicScrollBB.hpp"

using ByteBuffer = MagicScrollBB;

int
main() {
  auto buffer = ByteBuffer(1024);

  // Write some data
  buffer.write_string("Hello, world!");
  buffer.write_int(42);

  // Reset the internal cursor
  buffer.reset_cursor();

  // Read it back
  auto string_value = buffer.read_string();
  fmt::print("The string == {}\n", string_value);

  auto int_value = buffer.read_int();
  fmt::print("The int == {}\n", int_value);
}
