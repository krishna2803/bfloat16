#include "bfloat16.h"

#include <print>

int main() {
  const bfloat::bfloat16 x(-6.9f);

  // 11000000110111001100110011001101
  // 1100000011011100

  auto f = static_cast<float>(x);

  std::println("{}", x.get_bit_string());

  std::println("{}", f);

}