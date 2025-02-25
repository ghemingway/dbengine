// @author G. Hemingway, copyright 2025 - All rights reserved
#include "db/vl_int.h"
#include <gtest/gtest.h>

namespace {
// The fixture for testing VLInt parsing and writing
class VLIntTest : public ::testing::Test { };

//
TEST_F(VLIntTest, SimpleParsing)
{
    constexpr unsigned char data[2] = { 0x01, 0x02 };
    const auto [fstA, sndA] = VLInt::parse(data);
    EXPECT_EQ(fstA, 1);
    EXPECT_EQ(sndA, 1);

    const auto [fstB, sndB] = VLInt::parse(data + 1);
    EXPECT_EQ(fstB, 2);
    EXPECT_EQ(sndB, 1);
}
}
