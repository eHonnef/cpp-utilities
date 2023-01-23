/**
 * @file Tests.cpp
 * @brief Unit tests for the file @ref ByteUtilities.hpp
 *
 */

#include <ByteUtilities.hpp>
#include <catch_amalgamated.hpp>

/**************************************************************************************
 * Test Section for [Bit operation]
 **************************************************************************************/

TEMPLATE_TEST_CASE("Bit mask test", "[Bit operation]", int, long long int, size_t, uint16_t,
                   uint32_t, uint64_t) {
  constexpr TestType nValueA = 0x37AB;
  constexpr TestType nValueB = 0xB7AB;

  // 0011 0111 1010 1011 -> 0011 0110 0000 0000
  REQUIRE(ByteUtilities::MaskBits(nValueA, 9, 5) == 0x3600);

  // 0011 0111 1010 1011 -> 0000 0000 0000 0001
  REQUIRE(ByteUtilities::MaskBits(nValueA, 0, 1) == 0x0001);

  // 0011 0111 1010 1011 -> 0000 0000 0000 0000
  REQUIRE(ByteUtilities::MaskBits(nValueA, 0, 0) == 0x0000);

  // 1011 0111 1010 1011 -> 1000 0000 0000 0000
  REQUIRE(ByteUtilities::MaskBits(nValueB, 15, 1) == 0x8000);

  // 1011 0111 1010 1011 -> 0000 0000 0000 0000
  REQUIRE(ByteUtilities::MaskBits(nValueB, 15, 0) == 0x0000);
}

TEMPLATE_TEST_CASE("Bit mask test - compile time", "[Bit operation]", int, long long int, size_t,
                   uint16_t, uint32_t, uint64_t) {
  constexpr TestType nValueA = 0x37AB;
  constexpr TestType nValueB = 0xB7AB;

  // 0011 0111 1010 1011 -> 0011 0110 0000 0000
  REQUIRE((ByteUtilities::CreateBitMask<TestType, 9, 5>() & nValueA) == 0x3600U);

  // 0011 0111 1010 1011 -> 0000 0000 0000 0001
  REQUIRE((ByteUtilities::CreateBitMask<TestType, 0, 1>() & nValueA) == 0x0001U);

  // 0011 0111 1010 1011 -> 0000 0000 0000 0000
  REQUIRE((ByteUtilities::CreateBitMask<TestType, 0, 0>() & nValueA) == 0x0000U);

  // 1011 0111 1010 1011 -> 1000 0000 0000 0000
  REQUIRE((ByteUtilities::CreateBitMask<TestType, 15, 1>() & nValueB) == 0x8000U);

  // 0011 0111 1010 1011 -> 0000 0000 0000 0000
  REQUIRE((ByteUtilities::CreateBitMask<TestType, 15, 0>() & nValueB) == 0x0000U);
}

TEST_CASE("Bit slice test", "[Bit operation]") {
  // 0011 0111 1010 1011 -> 0000 0000 0001 1011
  REQUIRE(ByteUtilities::GetBitSlice(0x37AB, 9, 5) == 0x001B);
  // @todo: more test cases
}

/**************************************************************************************
 * Test Section for [Byte operation]
 **************************************************************************************/

TEST_CASE("Get byte test", "[Byte operation]") {
  // 0xAB CD EF 01 23 45 67 89
  constexpr uint64_t nInt = 0xABCDEF0123456789;

  REQUIRE(ByteUtilities::GetByte(nInt, 0) == 0x89u);
  REQUIRE(ByteUtilities::GetByte(nInt, 1) == 0x67u);
  REQUIRE(ByteUtilities::GetByte(nInt, 2) == 0x45u);
  REQUIRE(ByteUtilities::GetByte(nInt, 3) == 0x23u);
  REQUIRE(ByteUtilities::GetByte(nInt, 4) == 0x01u);
  REQUIRE(ByteUtilities::GetByte(nInt, 5) == 0xEFu);
  REQUIRE(ByteUtilities::GetByte(nInt, 6) == 0xCDu);
  REQUIRE(ByteUtilities::GetByte(nInt, 7) == 0xABu);
}
