// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <array>
#include <bit>

/**
 * Adapted from https://en.cppreference.com/w/cpp/numeric/byteswap
 * - needed if not on >= C++23
 * @tparam T
 * @param value
 * @return
 */
template <std::integral T> constexpr T byteswap(T value) noexcept {
  static_assert(std::has_unique_object_representations_v<T>,
                "T may not have padding bits");
  auto value_representation =
      std::bit_cast<std::array<std::byte, sizeof(T)>>(value);
  std::ranges::reverse(value_representation);
  return std::bit_cast<T>(value_representation);
}

#endif // UTIL_H
