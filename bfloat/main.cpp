#include "bfloat16.h"

#include <print>

using bfloat::bfloat16;

int main() {
  const bfloat16 x(7.75f);
  const bfloat16 y(-0.25f);

  const auto z = bfloat16::add(x, y);

  std::println("{} <- x", static_cast<float>(x));
  std::println("{} <- y", static_cast<float>(y));
  std::println("{} <- z", static_cast<float>(z));
}
