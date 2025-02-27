#include "bfloat16.h"

#include <print>

int main() {
  const bfloat::bfloat16 x = -6.9f;
  std::println("{}", x.value());
}