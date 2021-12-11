# TODOs

## (with versions)


* Add support for:
  - Absolute versus relative offsets via `MagicScrollBB::Cursor`.
  - Version: 0.2.1

* Add `long` as alias for `int64`
  - Version: 0.2.2

* Add support for little/big endian.
  - Version: 0.3.0
  - Pick a default (little or big)
    - Remove a bunch of places where I use `reinterpret_cast`

* Add Codec class based on "pointer to member" C++ semantics:
  - Version: 0.4.0
  - Use template programming to provide an interface where 
    - A client can use `&Object::member` syntax (same as `pybind11`)
  - See `todo/CODECs.md` for some examples found on the internet that use member-pointers to do serialize / deserialize.
  
## (without versions)

* Add some documentation.
* Add more examples.
* Add link to `KoboldLairSP`
* Add more methods from `java.nio.ByteBuffer`
  * Buffer.compact
  * https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html#compact
  * > The bytes between the buffer's current position and its limit, if any, are copied to the beginning of the buffer.
  * I have definitely done this before, but called it something else
