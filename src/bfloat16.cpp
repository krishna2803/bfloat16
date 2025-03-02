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

#if __BYTE_ORDER == __LITTLE_ENDIAN
  _value = ieee754_rep.u >> 16;
#endif // little endian

#if __BYTE_ORDER == __BIG_ENDIAN
  value = __builtin_bswap16(ieee754_rep.u >> 16);
#endif // big endian
}

auto bfloat16::get_val() const -> u16 { return _value; }

auto bfloat16::get_bit_string() const -> std::string {
  const std::string s = std::bitset<16>(_value).to_string();
  return s.substr(0, 1) + " " + s.substr(1, 8) + " " + s.substr(9, 7);
}

bfloat16::operator float() const {
  const union {
    const float f;
    const u32 u;
  } ieee754_rep{.u = static_cast<u32>(_value) << 16}; // currently LE only
  return ieee754_rep.f;
}

unsigned bfloat16::count_leading_zeros_mantissa() const {
  constexpr u8 digits = 8;
  u8 m = mantissa();
  if (!m)
    return digits;
  unsigned zero_bits = 0;
  for (unsigned shift = digits >> 1; shift; shift >>= 1) {
    if (const u8 tmp = m >> shift)
      m = tmp;
    else
      zero_bits |= shift;
  }

  // same as 8 bit but subtract 1 from the result
  return zero_bits >= 1 ? zero_bits - 1 : 0;
}
bfloat16 &bfloat16::shift_left(const unsigned shift_width) {
  if (shift_width >= 7) {
    exponent(0);
    mantissa(0);
  } else {
    exponent(exponent() - shift_width);
    mantissa(mantissa() << shift_width);
  }
  return *this;
}
bfloat16 &bfloat16::shift_right(const unsigned shift_width) {
  if (shift_width >= 7) {
    exponent(0);
    mantissa(0);
  } else {
    exponent(exponent() + shift_width);
    mantissa(mantissa() >> shift_width);
  }
  return *this;
}

auto bfloat16::add(const bfloat16 &a, const bfloat16 &b) -> bfloat16 {
  if (a.is_zero())
    return b;
  if (b.is_zero())
    return a;

  // this is where the implementation differs from the LLVM one. in the LLVM i
  // believe they are using explicit bits for the mantissa while i'm using
  // implicit. i cannot simply add the values of a and b mantissas so we need to
  // convert these by setting the implicit bit. luckily for us, bfloat16 uses 7
  // explicit bits for the mantissa so we can just use one byte to store all the
  // 7 explicit bits and also the implicit bit explicitly (lol) and then we can
  // perform the addition.

  u8 a_m = 0b10000000 | a.mantissa();
  u8 b_m = 0b10000000 | b.mantissa();

  const u8 exp = a.exponent() > b.exponent() ? a.exponent() : b.exponent();
  if (exp > b.exponent()) {
    b_m >>= (exp - b.exponent());
  } else if (exp > a.exponent()) {
    a_m >>= (exp - a.exponent());
  }

  bfloat16 result = ZERO();

  if (a.sign() == b.sign()) {
    result.sign(a.sign());
    u8 sum_m;
    result.exponent(__builtin_add_overflow(a_m, b_m, &sum_m) ? exp + 1 : exp);
    result.mantissa(sum_m);
    return result;
  }

  return result;
}

} // namespace bfloat
