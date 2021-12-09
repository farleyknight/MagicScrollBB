#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>

class MagicScrollBB {
public:
  using byte_t          = unsigned char;
  using data            = std::vector<byte_t>;
  using buffer_offset_t = std::int32_t;
  using buffer_size_t   = std::int32_t;
  using datetime_t      = std::chrono::system_clock::time_point;

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

  void
  reset_memory() {
    std::fill(data_.begin(), data_.end(), 0);
  }

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
   * read/write_bool
   */

  void
  write_bool(buffer_offset_t offset, bool b) {
    *reinterpret_cast<bool*>(ptr(offset)) = b;
  }

  bool
  read_bool(buffer_offset_t offset) const {
    return *reinterpret_cast<const bool*>(const_ptr(offset));
  }

  /*
   * read/write_int8
   */

  void
  write_int8(buffer_offset_t offset, int8_t n) {
    *reinterpret_cast<int8_t*>(ptr(offset)) = n;
  }

  int8_t
  read_int8(buffer_offset_t offset) const {
    return *reinterpret_cast<const int8_t*>(const_ptr(offset));
  }

  /*
   * read/write_int16
   */

  void
  write_int16(buffer_offset_t offset, int16_t n) {
    *reinterpret_cast<int16_t*>(ptr(offset)) = n;
  }

  int16_t
  read_int16(buffer_offset_t offset) const {
    return *reinterpret_cast<const int16_t*>(const_ptr(offset));
  }

  /*
   * read/write_int32
   */

  int32_t
  read_int32(buffer_offset_t offset) const {
    return *reinterpret_cast<const int32_t*>(const_ptr(offset));
  }

  void
  write_int32(buffer_offset_t offset, int32_t n) {
    *reinterpret_cast<int32_t*>(ptr(offset)) = n;
  }

  /*
   * read/write_int -- Alias for read/write_int32
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
   * read/write_int32
   */

  uint32_t
  read_uint32(buffer_offset_t offset) const {
    return *reinterpret_cast<const uint32_t*>(const_ptr(offset));
  }

  void
  write_uint32(buffer_offset_t offset, uint32_t n) {
    *reinterpret_cast<uint32_t*>(ptr(offset)) = n;
  }

  /*
   * read/write_int64
   */

  int64_t
  read_int64(buffer_offset_t offset) const {
    return *reinterpret_cast<const int64_t*>(const_ptr(offset));
  }

  void
  write_int64(buffer_offset_t offset, int64_t n) {
    *reinterpret_cast<int64_t*>(ptr(offset)) = n;
  }

  /*
   * read/write_uint64
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
   * read/write_float
   */

  void
  write_float(buffer_offset_t offset, float f) {
    *reinterpret_cast<float*>(ptr(offset)) = f;
  }

  float
  read_float(buffer_offset_t offset) const {
    return *reinterpret_cast<const float*>(const_ptr(offset));
  }

  /*
   * read/write_double
   */

  void
  write_double(buffer_offset_t offset, double d) noexcept {
    *reinterpret_cast<double*>(ptr(offset)) = d;
  }

  double
  read_double(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const double*>(const_ptr(offset));
  }

  /*
   * read/write_offset
   */

  void
  write_offset(buffer_offset_t offset, buffer_offset_t n) noexcept {
    *reinterpret_cast<buffer_offset_t*>(ptr(offset)) = n;
  }

  buffer_offset_t
  read_offset(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const buffer_offset_t*>(const_ptr(offset));
  }

  /*
   * read/write_enum<EnumT>
   */

  template<typename EnumT>
  void
  write_enum(buffer_offset_t offset, EnumT value) noexcept {
    *reinterpret_cast<EnumT*>(ptr(offset)) = value;
  }

  template<typename EnumT>
  EnumT
  read_enum(buffer_offset_t offset) const noexcept {
    return *reinterpret_cast<const EnumT*>(const_ptr(offset));
  }

  /*
   * read/write_buffer
   */

  void
  write_buffer(buffer_offset_t offset,
               const MagicScrollBB& buffer) noexcept
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
   * read/write_string32
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
   * read/write_string
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
   * read/write_datetime
   */

  void
  write_datetime(buffer_offset_t offset, datetime_t datetime) noexcept {
    using namespace std::chrono;
    auto micro_duration = time_point_cast<microseconds>(datetime);
    uint64_t micro_value = micro_duration.time_since_epoch().count();
    write_uint64(offset, micro_value);
  }

  datetime_t
  read_datetime(buffer_offset_t offset) {
    uint64_t value = read_uint64(offset);
    using namespace std::chrono;
    return datetime_t(microseconds(value));
  }

  data&
  as_byte() {
    return data_;
  }

  const data&
  as_bytes() const {
    return data_;
  }

  byte_t*
  ptr() {
    return data_.data();
  }

  byte_t*
  ptr(buffer_offset_t offset) {
    return data_.data() + offset;
  }

  const byte_t*
  const_ptr() const {
    return data_.data();
  }

  const byte_t*
  const_ptr(buffer_offset_t offset) const {
    return data_.data() + offset;
  }

  char*
  char_ptr() {
    return reinterpret_cast<char*>(data_.data());
  }

  const char*
  char_ptr() const {
    return reinterpret_cast<const char*>(data_.data());
  }

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
};
