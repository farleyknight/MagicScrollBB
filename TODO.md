# TODOs

## (with versions)

* Add `long` as alias for `int64`
  - Version: 0.2.2
  
* Add `ByteBuffer::from_string(const std::string value)`
  - Version: 0.2.3

* Add support for little/big endian.
  - Version: 0.3.0
  - Pick a default (little or big)
    - Remove a bunch of places where I use `reinterpret_cast`

## Codec Offshoot Project

* Add Codec class based on "pointer to member" C++ semantics:
  - Version: 0.4.0
  - Use template programming to provide an interface where 
    - A client can use `&Object::member` syntax (same as `pybind11`)
  - See `todo/CODECs.md`
    - Those examples on the internet that use member-pointers.
    - Those examples make serialize / deserialize easy.
    
* NOTE: The "Codec" version of MagicScrollBB will not happen here.
  - Instead it will be a separate project called `PolymorphSpellSD`
    - SD = Serializer & Deserializer
  - If I ever decide I need Codec support, it should go into that project.

* NOTE: After deciding to move "Codec" to a new project...
  - I think that the refactoring for endianness (removing `reinterpret_cast`)
  - This can possibly be absorbed by `PolymorphSpellSD` 
  - Why? Because serialization & deserialization is handled by `reinterpret_cast`
    - They are related functions
    - Make `MagicScrollBB` depend on functions in `PolymorphSpellSD`

## (without versions)

* Add some documentation.
  - Document `read/write_enum<EnumT>`
  - Put it in the `README.md`
  
* Add more examples.
  - Maybe network packets?
  - Best example is to just link to `KoboldLairSP`
  
* Add link to `KoboldLairSP`

* Add more methods from `java.nio.ByteBuffer`
  * Buffer.compact
  * https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html#compact
  * > The bytes between the buffer's current position and its limit, if any, are copied to the beginning of the buffer.
  * I have definitely done this before, but called it something else
