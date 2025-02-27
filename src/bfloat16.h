//
// Created by krishna on 24/2/25.
//

#ifndef BFLOAT16_H
#define BFLOAT16_H

#include <bitset>
#include <cstdint>
#include <string>

namespace bfloat {

using u16 = uint16_t;
using u32 = uint32_t;

class bfloat16 {
private:
  u16 val;

  bfloat16(u16 u = 0);

public:
  bfloat16(const bfloat16 &) = default;

  bfloat16(float f = 0.0f);

  [[nodiscard]]
  auto get_val() const -> u16;
  [[nodiscard]] std::string value() const;

  static constexpr bfloat16 INF() {
    return {static_cast<u16>(0b0'11111111'0000000)};
  }

  static constexpr bfloat16 NEG_INF() {
    return {static_cast<u16>(0b1'11111111'0000000u)};
  }

  static constexpr bfloat16 NAN() {
    return {static_cast<u16>(0b1'11111111'0000001u)};
  }
};

} // bfloat

#endif //BFLOAT16_H
