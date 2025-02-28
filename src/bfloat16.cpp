//
// Created by krishna on 24/2/25.
//

#include "bfloat16.h"

namespace bfloat {
bfloat16::bfloat16(const float f) {
  const union ieee754 {
    const float f;
    const u32 u;
  } ieee754_rep{f};

#if	__BYTE_ORDER == __LITTLE_ENDIAN
  this->value = ieee754_rep.u >> 16;
#endif // little endian

#if	__BYTE_ORDER == __BIG_ENDIAN
  this->value = __builtin_bswap16(ieee754_rep.u >> 16);
#endif // little endian
}

bfloat16::bfloat16(const u16 u) {
  this->value = u;
}

auto bfloat16::get_val() const -> u16 {
  return this->value;
}

auto bfloat16::get_bit_string() const -> std::string {
  return std::bitset<16>(this->value).to_string();
}

bfloat16::operator float() const {
  const union ieee754 {
    const float f;
    mutable u32 u;
  } ieee754_rep{};
  ieee754_rep.u = static_cast<u32>(this->value) << 16;
  return ieee754_rep.f;
}

} // bfloat