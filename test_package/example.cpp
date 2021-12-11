#include <fmt/core.h>
#include <MagicScrollBB.hpp>

using ByteBuffer = MagicScrollBB;

enum Color : std::int32_t {
  RED = 1,
  BLUE = 2,
  GREEN = 3
};

int main() {
  auto buffer = ByteBuffer(1024);

  // Write some data
  buffer.write_string("Hello, world!");
  buffer.write_int(42);
  buffer.write_long(2147483647);
  buffer.write_enum<Color>(BLUE);

  // Reset the internal cursor
  buffer.reset_cursor();

  // Read it back
  fmt::print("The string == {}\n",
             buffer.read_string());
  fmt::print("The int == {}\n",
             buffer.read_int());
  fmt::print("The long == {}\n",
             buffer.read_long());
  fmt::print("The enum == {}\n",
             buffer.read_enum_as_string<Color>());

  // One nice convenience method:
  auto string_buffer = ByteBuffer::from_string("foobar");
  fmt::print("string_buffer has content: {}\n",
             string_buffer.read_string());
}
