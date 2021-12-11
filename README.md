# MagicScrollBB

(BB = ByteBuffer)

Hand-crafted C++ version of `java.nio.ByteBuffer`.

## How to use

```c++
#include <MagicScrollBB.hpp>

using Buffer = MagicScrollBB;

int main() {
  auto buffer = Buffer(1024);
  buffer.write_string(0, "Hello, world");
  auto value = buffer.read_string(0);
  printf("%s", value);
}
```

## TODO

* Add some documentation.
* Add more examples.
* Add link to `KoboldLairSP`
* Add more methods from `java.nio.ByteBuffer`
  * Buffer.compact
  * https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html#compact
  * > The bytes between the buffer's current position and its limit, if any, are copied to the beginning of the buffer.
  * I have definitely done this before, but called it something else
