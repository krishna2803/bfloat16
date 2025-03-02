#include "bfloat16.h"

#include <print>

using bfloat::bfloat16;

int main() {
  bfloat16 x = 7.75f;
  bfloat16 y = 0.5f;

  bfloat16 z = bfloat16::add(x, y);

  std::println("{} <- x", static_cast<float>(x));
  std::println("{} <- y", static_cast<float>(y));
  std::println("{} <- z", static_cast<float>(z));
}
