TODO:

* 0.2.1 - Added relative methods, that do not require an index.
          This should mirror the same methods in `java.nio.ByteBuffer`

* Add support for:
  - Absolute versus relative offsets via `MagicScrollBB::Cursor`.
  - Version: 0.2.1
    
* Add support for little/big endian.
  - Version: 0.3.0
  - Pick a default (little or big)
    - Remove a bunch of places where I use `reinterpret_cast`

* Add Codec class based on "pointer to member" C++ semantics:
  - Version: 0.4.0
  - Use template programming to provide an interface where 
    - A client can use `&Object::member` syntax (same as `pybind11`)
  - See `todo/CODECs.md` for some examples found on the internet that use member-pointers to do serialize / deserialize.
  

