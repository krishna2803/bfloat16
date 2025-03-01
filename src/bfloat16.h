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

class bfloat16 {
private:
  u16 value;

  explicit bfloat16(u16 u = 0);

public:
  bfloat16(const bfloat16 &) = default;

  explicit bfloat16(float f = 0.0f);

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
