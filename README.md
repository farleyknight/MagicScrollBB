# MagicScrollBB

(BB = ByteBuffer)

Hand-crafted C++ version of java.nio.ByteBuffer

## How to use

```c++
#include <MagicScrollBB.hpp>

using Buffer = MagicScrollBB;

void main() {
  buffer = Buffer(1024);
  buffer.write_string(0, "Hello, world");
  auto value = buffer.read_string(0);
  printf("%s", value);
}
```
