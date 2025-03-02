//
// Created by krishna on 24/2/25.
//

#ifndef BFLOAT16_H
#define BFLOAT16_H

#include <bitset>
#include <cstdint>
#include <string>

namespace bfloat {

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint16_t;

class bfloat16 {
private:
  explicit constexpr bfloat16(const u16 u = 0) { this->_value = u; }

  explicit constexpr bfloat16(const u32 u = 0)
      : bfloat16(static_cast<u16>(u)) {}

  static constexpr u16 SIGN_LEN = 1;
  static constexpr u16 EXPONENT_LEN = 8;
  static constexpr u16 MANTISSA_LEN = 7;

#if __BYTE_ORDER == __LITTLE_ENDIAN
  static constexpr u16 SIGN_MASK = 0b1'00000000'0000000;
  static constexpr u16 EXPONENT_MASK = 0b0'11111111'0000000;
  static constexpr u16 MANTISSA_MASK = 0b0'00000000'1111111;

  static constexpr u16 SIGN_OFFSET = MANTISSA_LEN + EXPONENT_LEN;
  static constexpr u16 EXPONENT_OFFSET = MANTISSA_LEN;
  static constexpr u16 MANTISSA_OFFSET = 0;

#elif __BYTE_ORDER == __BIG_ENDIAN // little endian
  static constexpr u16 SIGN_MASK = 0b1'00000000'0000000;
  static constexpr u16 EXPONENT_MASK = 0b0'11111111'0000000;
  static constexpr u16 MANTISSA_MASK = 0b0'00000000'1111111;
#endif                             // big endian

public:
  u16 _value;

  bfloat16(const bfloat16 &) = default;
  bfloat16 &operator=(const bfloat16 &) = default;
  bfloat16(float f = 0.0f);

  static constexpr bfloat16 INF() { return bfloat16(0b0'11111111'0000000u); }

  static constexpr bfloat16 NEG_INF() {
    return bfloat16(0b1'11111111'0000000u);
  }

  static constexpr bfloat16 NAN() { return bfloat16(0b1'11111111'0000001u); }

  static constexpr bfloat16 ZERO() { return bfloat16(0u); }

  [[nodiscard]]
  constexpr auto sign() const -> u8 {
    return (SIGN_MASK & _value) >> SIGN_OFFSET;
  }

  [[nodiscard]]
  constexpr auto exponent() const -> u8 {
    return (EXPONENT_MASK & _value) >> EXPONENT_OFFSET;
  }

  [[nodiscard]]
  constexpr auto mantissa() const -> u8 {
    return (MANTISSA_MASK & _value) >> MANTISSA_OFFSET;
  }

  void sign(const u8 s) {
    _value = (_value & ~SIGN_MASK) |
             ((static_cast<u16>(s) << SIGN_OFFSET) & SIGN_MASK);
  }

  void exponent(const u8 e) {
    _value = (_value & ~EXPONENT_MASK) |
             ((static_cast<u16>(e) << EXPONENT_OFFSET) & EXPONENT_MASK);
  }

  void mantissa(const u8 m) {
    _value = (_value & ~MANTISSA_MASK) |
             ((static_cast<u16>(m) << MANTISSA_OFFSET) & MANTISSA_MASK);
  }

  [[nodiscard]]
  bool is_zero() const {
    return !exponent() && !mantissa();
  }

  bfloat16 &shift_left(unsigned shift_width);

  bfloat16 &shift_right(unsigned shift_width);

  static auto add(const bfloat16 &a, const bfloat16 &b) -> bfloat16;

  [[nodiscard]]
  auto get_val() const -> u16;

  [[nodiscard]]
  auto get_bit_string() const -> std::string;

  explicit operator float() const;
};

} // namespace bfloat

#endif // BFLOAT16_H
