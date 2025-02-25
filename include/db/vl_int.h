// @author Graham Hemingway @copyright 2025 - All rights reserved

#ifndef VL_INT_H
#define VL_INT_H

#include <cstdint>
#include <utility>

class VarInt {
public:
  static std::pair<int64_t, uint8_t> parse(const char *buffer);

  explicit VarInt(int64_t value = 0);

private:
  int64_t value;
};

#endif // VL_INT_H
