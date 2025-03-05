//
// Created by krishna on 4/3/25.
//

#include "../bfloat/bfloat16.h"

using bfloat::bfloat16;

#include "gtest/gtest.h"

TEST(bfloat16, SanityCheck) { EXPECT_EQ(1 + 1, 2); }

TEST(bfloat16, Float32toBfloat32) {
  // 0 01111111 10000000000000000000000
  constexpr float one_point_five = 1.5f;
  EXPECT_EQ(bfloat16(one_point_five).get_val(), 0b0011111111000000);

  // 1 01111111 01000000000000000000000
  constexpr float negative_one_point_two_five = -1.25f;
  EXPECT_EQ(bfloat16(negative_one_point_two_five).get_val(),
            0b1011111110100000);

  // 0 10000010 01001101011100001010010
  constexpr float ten_point_four_two = 10.42f;
  EXPECT_EQ(bfloat16(ten_point_four_two).get_val(), 0b0100000100100110);

  // 1 10000101 00010101111000010100100
  constexpr float negative_size_nine_point_four_seven = -69.47f;
  EXPECT_EQ(bfloat16(negative_size_nine_point_four_seven).get_val(),
            0b1100001010001010);
}

TEST(bfloat16, EqualityTests) {
  constexpr float f1 = 0.25f;
  constexpr float f2 = -3.72f;
  constexpr float f3 = f1 + f2;
  EXPECT_EQ(bfloat16(f1 + f2), bfloat16(f3));
}

TEST(bfloat16, AdditionTests) {
  constexpr float f1 = 7.75f;
  constexpr float f2 = 0.25f;
  const bfloat16 bf1(f1);
  const bfloat16 bf2(f2);
  const auto bf3 = bfloat16::add(bf1, bf2);
  const bfloat16 bf4(f1 + f2);
  EXPECT_EQ(bf3, bf4);
}
