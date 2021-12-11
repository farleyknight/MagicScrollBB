# MagicScrollBB

(BB = ByteBuffer)

Hand-crafted C++ version of `java.nio.ByteBuffer`.

## How to use

```c++
#include <fmt/core.h>
#include <MagicScrollBB.hpp>

using ByteBuffer = MagicScrollBB;

int main() {
  auto buffer = ByteBuffer(1024);
  // Use `write` methods to write primitive data types, such as
  // - Various flavors of `int(8|16|32|64)_t`
  // - `std::string` (using int32 length prefix)
  // - `write_enum<EnumT>` for some given type `EnumT`
  buffer.write_string("Hello, world!");
  
  // Note that the above could have been done using the "absolute" 
  // version of `write_string`:
  //
  // > buffer.write_string(0, "Hello, world");

  // To read back our two values, let's reset the cursor
  buffer.reset_cursor();

  // The relative versions use an internal `Cursor` object to keep
  // track of where the offset should be at, after doing a read/write
  // of a data type.
  auto string_value = buffer.read_string();
  fmt::print("The string == {}\n", value);
  
  auto int_value = buffer.read_int();
  fmt::print("The integer == {}\n", value);
}
```

## Features

Supports the following primitive types
* bool
* int (alias for `int32`)
* long (alias for `int64`) [TODO]
* string (alias for `string32`
  - `string32`is a character array prefixed with int32 as the array size
* Other `ByteBuffer` objects

Each of these data types has 4 methods:

* Absolute offset
  - `read_<primitive>(offset)`
  - `write_<primitive>(offset, value)`
* Relative offset (using internal `Cursor`)
  - `read_<primitive>()`
  - `write_<primitive(value)`
  - The cursor will update after each relative operation.

