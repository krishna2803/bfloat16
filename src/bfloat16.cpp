//
// Created by krishna on 24/2/25.
//

#include "bfloat16.h"

#include <ieee754.h>

namespace bfloat {
bfloat16::bfloat16(const float f) {
  const union ieee754_float ieee754_f{f};
  this->val = (ieee754_f.ieee.negative << 15) | (
                (ieee754_f.ieee.exponent & 0xff) << 7) | (
                ((ieee754_f.ieee.mantissa >> 16) & 0x7f
                )
              );
}

bfloat16::bfloat16(const u16 u) {
  this->val = u;
}

auto bfloat16::get_val() const -> u16 {
  return this->val;
}

auto bfloat16::value() const -> std::string {
  return std::bitset<16>(this->val).to_string();
}
} // bfloat