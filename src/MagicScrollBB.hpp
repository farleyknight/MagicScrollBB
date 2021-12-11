#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

// TODO: Generate documentation
//

/*
 * NOTE: Just like javax.nio.ByteBuffer, we have absolute & relative versions of all of the data types provided:
 * - bool
 * - int8
 * - int16
 * - int32
 *   - ALIAS: int
 * - uint32
 * - int64
 * - uint64
 * - string32
 *   - ALIAS: string
 */

class MagicScrollBB {
public:
  using byte_t          = unsigned char;
  using data            = std::vector<byte_t>;
  using buffer_offset_t = std::int32_t;
  using buffer_size_t   = std::int32_t;
  using datetime_t      = std::chrono::system_clock::time_point;

  // Simple Cursor object for relative versions of methods.
  class Cursor {
  public:
    Cursor(buffer_offset_t offset)
      : offset_ (offset)
    {}

    buffer_offset_t
    offset() const noexcept {
      return offset_;
    }

    void
    reset() noexcept {
      offset_ = 0;
    }

    void
    forward(int32_t steps) noexcept {
      offset_ += steps;
    }

    void
    rewind(int32_t steps) noexcept {
      offset_ -= steps;
    }

  private:
    buffer_offset_t offset_ = 0;
  };


  MagicScrollBB() {
    data_.resize(0);
  }

  MagicScrollBB(buffer_size_t size) {
    data_.resize(size);
  }

  buffer_size_t
  size() const {
    return data_.size();
  }

  /*
   * Fill buffer entirely with zeros.
   */

  void
  reset_memory() {
    std::fill(data_.begin(), data_.end(), 0);
  }

  /*
   * Reset cursor back to starting position.
   */

  void
  reset_cursor() {
    cursor_.reset();
  }

  /*
   * Copy a segment of bytes.
   * - source : Where to begin the copy of bytes
   * - dest   : Where to place the new bytes
   * - size   : How many to bytes to copy
   *
   * If you are comfortable w/ Python's slice syntax,
   * then you can think of `copy` doing this to a `Buffer`:
   *
   * >> buffer[dest:dest+size] = buffer[source:source+size]
   *
   */

  void
  copy(buffer_offset_t source,
       buffer_offset_t dest,
       buffer_size_t size)
    noexcept
  {
    std::memcpy(ptr(dest),
                ptr(source),
                size);
  }

  /*
   * absolute read/write_bool
   */

  bool
  read_bool(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const bool*>(const_ptr(offset));
  }

  void
  write_bool(buffer_offset_t offset, bool b) noexcept {
    *reinterpret_cast<bool*>(ptr(offset)) = b;
  }

  /*
   * relative read/write_bool
   */

  bool
  read_bool() noexcept {
    auto value = read_bool(cursor.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_bool(bool b) {
    write_bool(cursor.offset(), b);
    cursor_.forward(sizeof(b));
  }

  /*
   * absolute read/write_int8
   */

  int8_t
  read_int8(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const int8_t*>(const_ptr(offset));
  }

  void
  write_int8(buffer_offset_t offset, int8_t n) {
    *reinterpret_cast<int8_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_int8
   */

  int8_t
  read_int8() noexcept {
    auto value = read_int8(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_int8(int8_t n) noexcept {
    write_int8(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_int16
   */

  int16_t
  read_int16(buffer_offset_t offset) const noexcept {
    // TODO: Take care of endian-ness here!
    return *reinterpret_cast<const int16_t*>(const_ptr(offset));
  }

  void
  write_int16(buffer_offset_t offset, int16_t n) {
    // TODO: Take care of endian-ness here!
    *reinterpret_cast<int16_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_int16
   */

  int16_t
  read_int16() noexcept {
    auto value = read_int16(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_int16(int16_t n) {
    write_int16(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_int32
   */

  int32_t
  read_int32(buffer_offset_t offset) const noexcept {
    // TODO: Take care of endian-ness here!
    return *reinterpret_cast<const int32_t*>(const_ptr(offset));
  }

  void
  write_int32(buffer_offset_t offset, int32_t n) {
    // TODO: Take care of endian-ness here!
    *reinterpret_cast<int32_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_int32
   */

  int32_t
  read_int32() noexcept {
    auto value = read_int32(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_int32(int32_t n) noexcept {
    write_int32(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_int -- Alias for absolute read/write_int32
   */

  int
  read_int(buffer_offset_t offset) const {
    return read_int32(offset);
  }

  void
  write_int(buffer_offset_t offset, int n) {
    write_int32(offset, n);
  }

  /*
   * relative read/write_int -- Alias for relative read/write_int32
   */

  int
  read_int() const {
    return read_int32();
  }

  void
  write_int(int n) {
    write_int32(n);
  }

  /*
   * absolute read/write_uint32
   */

  uint32_t
  read_uint32(buffer_offset_t offset) const {
    // TODO: Take care of endian-ness here!
    return *reinterpret_cast<const uint32_t*>(const_ptr(offset));
  }

  void
  write_uint32(buffer_offset_t offset, uint32_t n) {
    // TODO: Take care of endian-ness here!
    *reinterpret_cast<uint32_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_uint32
   */

  uint32_t
  read_uint32(buffer_offset_t offset) const {
    auto value = read_uint32(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_uint32(uint32_t n) {
    write_uint32(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_int64
   */

  int64_t
  read_int64(buffer_offset_t offset) const noexcept {
    // TODO: Take care of endian-ness here!
    return *reinterpret_cast<const int64_t*>(const_ptr(offset));
  }

  void
  write_int64(buffer_offset_t offset, int64_t n) {
    // TODO: Take care of endian-ness here!
    *reinterpret_cast<int64_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_int64
   */

  int64_t
  read_int64() noexcept {
    auto value = read_int64(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_int64(int64_t n) noexcept {
    write_int64(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_uint64
   */

  int64_t
  read_uint64(buffer_offset_t offset) const {
    return *reinterpret_cast<const uint64_t*>(const_ptr(offset));
  }

  void
  write_uint64(buffer_offset_t offset, uint64_t n) {
    *reinterpret_cast<uint64_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_uint64
   */

  int64_t
  read_uint64(buffer_offset_t offset) noexcept {
    auto value = read_uint64(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_uint64(buffer_offset_t offset, uint64_t n) {
    write_uint64(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_float
   */

  float
  read_float(buffer_offset_t offset) const {
    return *reinterpret_cast<const float*>(const_ptr(offset));
  }

  void
  write_float(buffer_offset_t offset, float f) {
    *reinterpret_cast<float*>(ptr(offset)) = f;
  }

  /*
   * relative read/write_float
   */

  float
  read_float() noexcept {
    auto value = read_float(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_float(float f) {
    write_float(cursor_.offset(), f);
    cursor_.forward(sizeof(f));
  }

  /*
   * absolute read/write_double
   */

  double
  read_double(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const double*>(const_ptr(offset));
  }

  void
  write_double(buffer_offset_t offset, double d) noexcept {
    *reinterpret_cast<double*>(ptr(offset)) = d;
  }

  /*
   * relative read/write_double
   */

  double
  read_double() noexcept {
    auto value = read_double(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_double(double d) noexcept {
    write_double(cursor_.offset(), d);
    cursor_.forward(sizeof(d));
  }

  /*
   * absolute read/write_offset
   */

  buffer_offset_t
  read_offset(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const buffer_offset_t*>(const_ptr(offset));
  }

  void
  write_offset(buffer_offset_t offset, buffer_offset_t n) noexcept {
    *reinterpret_cast<buffer_offset_t*>(ptr(offset)) = n;
  }

  /*
   * relative read/write_offset
   */

  buffer_offset_t
  read_offset() noexcept {
    auto value = read_offset(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  void
  write_offset(buffer_offset_t n) noexcept {
    write_offset(cursor_.offset(), n);
    cursor_.forward(sizeof(n));
  }

  /*
   * absolute read/write_enum<EnumT>
   */

  template<typename EnumT>
  EnumT
  read_enum(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const EnumT*>(const_ptr(offset));
  }

  template<typename EnumT>
  void
  write_enum(buffer_offset_t offset, EnumT value) noexcept {
    *reinterpret_cast<EnumT*>(ptr(offset)) = value;
  }

  /*
   * relative read/write_enum<EnumT>
   */

  template<typename EnumT>
  EnumT
  read_enum() const noexcept {
    auto value = read_enum<EnumT>(cursor_.offset());
    cursor_.forward(sizeof(value));
    return value;
  }

  template<typename EnumT>
  void
  write_enum(EnumT value) noexcept {
    write_enum<EnumT>(cursor_.offset(), value);
    cursor_.forward(sizeof(value));
  }

  /*
   * absolute read/write_buffer
   */

  void
  write_buffer(buffer_offset_t offset,
               MagicScrollBB const& buffer) noexcept
  {
    std::memcpy(ptr(offset),
                buffer.char_ptr(),
                buffer.size());
  }

  void
  read_buffer(buffer_offset_t offset,
              MagicScrollBB& buffer) const noexcept
  {
    std::memcpy(buffer.char_ptr(),
                const_ptr(offset),
                buffer.size());
  }

  /*
   * relative read/write_buffer
   */

  void
  write_buffer(MagicScrollBB const& buffer) noexcept
  {
    write_buffer(cursor_.offset(), buffer);
    cursor_.forward(buffer.size());
  }

  void
  read_buffer(MagicScrollBB& buffer) const noexcept
  {
    read_buffer(cursor_.offset(), buffer);
    cursor_.forward(buffer.size());
  }

  /*
   * absolute read/write_string32
   */

  const std::string
  read_string32(buffer_offset_t offset) const noexcept {
    int32_t size;
    std::memcpy(&size,
                const_ptr(offset),
                sizeof(int32_t));

    int32_t data_size = data_.size();

    auto string_start_offset = offset + sizeof(int32_t);
    auto start_ptr = const_ptr(string_start_offset);
    auto end_ptr   = start_ptr + size;

    return std::string(start_ptr, end_ptr);
  }

  void
  write_string32(buffer_offset_t offset,
                 const std::string value) noexcept
  {
    int32_t size = value.size();

    auto c_string = reinterpret_cast<const byte_t*>(value.c_str());

    std::memcpy(ptr(offset),
                &size,
                sizeof(int32_t));

    std::memcpy(ptr(offset + sizeof(int32_t)),
                c_string,
                size);
  }

  /*
   * relative read/write_string32
   */

  const std::string
  read_string32() noexcept
  {
    auto value = read_string32(cursor_.offset());
    cursor_.forward(value.size() + sizeof(int32_t));
    return value;
  }

  void
  write_string32(const std::string value) noexcept
  {
    write_string32(cursor_.offset(), value);
    cursor_.forward(value.size() + sizeof(int32_t));
  }

  /*
   * absolute read/write_string - Alias for absolute read/write_string32
   */

  const std::string
  read_string(buffer_offset_t offset) const noexcept {
    return read_string32(offset);
  }

  void
  write_string(buffer_offset_t offset,
               const std::string value) {
    write_string32(offset, value);
  }

  /*
   * relative read/write_string - Alias for relative read/write_string32
   */

  const std::string
  read_string() noexcept {
    return read_string32();
  }

  void
  write_string(const std::string value) noexcept {
    write_string32(value);
  }

  /*
   * absolute read/write_datetime
   */

  datetime_t
  read_datetime(buffer_offset_t offset)
    const noexcept
  {
    uint64_t value = read_uint64(offset);
    using namespace std::chrono;
    return datetime_t(microseconds(value));
  }

  void
  write_datetime(buffer_offset_t offset,
                 datetime_t datetime)
    noexcept
  {
    using namespace std::chrono;
    auto micro_duration = time_point_cast<microseconds>(datetime);
    uint64_t micro_value = micro_duration.time_since_epoch().count();
    write_uint64(offset, micro_value);
  }

  /*
   * relative read/write_datetime
   */

  datetime_t
  read_datetime() noexcept {
    auto value = read_datetime(cursor_.offset());

    return value;
  }

  /*
   * Accessing the underlying data as `vector<byte_t>`
   */

  data&
  as_byte() {
    return data_;
  }

  const data&
  as_bytes() const {
    return data_;
  }

  /*
   * Accessing the underlying data as `byte*`
   */

  byte_t*
  ptr() {
    return data_.data();
  }

  byte_t*
  ptr(buffer_offset_t offset) {
    return data_.data() + offset;
  }

  /*
   * Accessing the underlying data as `const byte*`
   */

  const byte_t*
  const_ptr() const {
    return data_.data();
  }

  const byte_t*
  const_ptr(buffer_offset_t offset) const {
    return data_.data() + offset;
  }

  /*
   * Accessing the underlying data as `char*`
   */

  char*
  char_ptr() {
    return reinterpret_cast<char*>(data_.data());
  }

  const char*
  char_ptr() const {
    return reinterpret_cast<const char*>(data_.data());
  }

  /*
   * Comparison operators
   */

  bool
  operator==(const MagicScrollBB& other) const noexcept {
    return data_ == other.as_bytes();
  }

  bool
  operator!=(const MagicScrollBB& other) const noexcept {
    return data_ != other.as_bytes();
  }

private:
  data data_;
  Cursor cursor_ {0};
};
