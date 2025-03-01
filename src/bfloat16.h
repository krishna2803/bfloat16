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

  explicit bfloat16(float f = 0.0f);
  static constexpr bfloat16 ZERO() { return bfloat16(0u); }

  [[nodiscard]]
  auto get_val() const -> u16;

  [[nodiscard]]
  auto get_bit_string() const -> std::string;

  explicit operator float() const;

  static constexpr bfloat16 INF() {
    return bfloat16(static_cast<u16>(0b0'11111111'0000000));
  }

  static constexpr bfloat16 NEG_INF() {
    return bfloat16(static_cast<u16>(0b1'11111111'0000000u));
  }

  static constexpr bfloat16 NAN() {
    return bfloat16(static_cast<u16>(0b1'11111111'0000001u));
  }
};

} // bfloat

#endif //BFLOAT16_H
