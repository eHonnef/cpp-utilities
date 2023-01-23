/**
 * @file ByteUtilities.hpp
 * @author eHonnef (contact@honnef.dev)
 * @brief Byte operations and utilities.
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright (c) 2023 Honnef
 *
 * MIT License
 *
 * Copyright (c) 2023 Honnef
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ********************************************************************************/
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <type_traits>

/**
 * @brief Namespace containing the static utilitary functions for bytes/bits operations.
 * All functions does not throw exceptions.
 *
 */
namespace ByteUtilities {

/**
 * @brief Create a Bit Mask integer. Does not throw exception.
 * Usage Example: aInt & CreateBitMask(0, 10). // Will mask the first 10 bits of aInt
 *
 * @tparam T Type of the bitmask, should be any integer
 * @param nPos Position of the first bit to make the mask.
 * @param nLen Number of bits to include in the bitmask.
 * @return T The bit mask.
 */
template <typename T> static inline T CreateBitMask(size_t nPos, size_t nLen) noexcept {
  if constexpr (!std::is_integral_v<T>)
    static_assert("T should be an integer");

  return ((1U << nLen) - 1U) << nPos;
}

/**
 * @brief Create a Bit Mask integer in compile time. Throw a compile time error if _nPos is bigger
 * than T in bits, or if _nLen + _nPos is bigger than T in bits.
 * Does not throw exception.
 * Usage Example: aInt & CreateBitMask<int, 0, 10>(). // Will mask the first 10 bits of aInt
 *
 * @tparam T Type of the bitmask, should be any integer
 * @param nPos Position of the first bit to make the mask.
 * @param nLen Number of bits to include in the bitmask.
 * @return constexpr T The bit mask.
 */
template <typename T, size_t _nPos, size_t _nLen>
constexpr static inline T CreateBitMask() noexcept {
  if constexpr (!std::is_integral_v<T> && (_nPos < (sizeof(T) * 8) - 1) &&
                ((_nLen + _nPos) <= (sizeof(T) * 8)))
    static_assert(
        "T should be an integer, _nPos < sizeof T in bits, _nLen + _nPos <= sizeof T in bits");

  return ((1U << _nLen) - 1U) << _nPos;
}

/**
 * @brief Masks the bits of @ref nInt. Does not throw exception.
 * Usage Example: MaskBits(aInt, 0, 10). // Will mask the first 10 bits of aInt
 *
 * @see @ref CreateBitMask.
 * @tparam T Type of the integer, should be any integer.
 * @param nInt Integer to mask.
 * @param nPos Position of the first bit to mask.
 * @param nLen Number of bits to mask.
 * @return T The masked integer.
 */
template <typename T> static inline T MaskBits(T nInt, size_t nPos, size_t nLen) noexcept {
  if constexpr (!std::is_integral_v<T>)
    static_assert("T should be an integer");

  return nInt & CreateBitMask<T>(nPos, nLen);
}

/**
 * @brief Return an integer with the slice of bits of @ref nInt shifted to the right. Does not throw
 * exception. Usage example: GetBitSlice(0x37AB, 9, 5) will return 0x001B. Which the binary will
 * look like: 0011 0111 1010 1011 -> 0000 0000 0001 1011
 *
 * @tparam T Type of the integer, should be any integer.
 * @param nInt Integer to slice.
 * @param nPos Position of the first bit to slice.
 * @param nLen Slice length.
 * @return T The integer with the slice in the least significative bits.
 */
template <typename T> static inline T GetBitSlice(T nInt, size_t nPos, size_t nLen) noexcept {
  if constexpr (!std::is_integral_v<T>)
    static_assert("T should be an integer");

  return MaskBits(nInt, nPos, nLen) >> nPos;
}

/**
 * @brief Returns the byte at Nth position of the integer @ref nInt. Does not throw exception.
 * Usage example: GetByte(0xAB01CD, 1) // Will return 0x01.
 *
 * @tparam T Type of the integer, should be any integer.
 * @param nInt Integer to get the byte from.
 * @param nByte The byte position.
 * @return uint8_t The byte from @ref nInt.
 */
template <typename T> static inline uint8_t GetByte(T nInt, size_t nByte) noexcept {
  if constexpr (!std::is_integral_v<T>)
    static_assert("T should be an integer");

  return (nInt >> (8 * nByte)) & 0xff;
}

}; // namespace ByteUtilities
