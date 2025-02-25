// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/vl_int.h"

auto VLInt::parse(const unsigned char* charBuffer) -> std::pair<int64_t, uint8_t>
{
    size_t offset = 0;
    uint8_t size = 0;
    int64_t result = 0;
    /*
    let mut size = 0;
    let mut result = 0;

    while size < 8 && charBuffer[offset] >= 0b1000_0000 {
        result |= ((charBuffer[offset] as i64) & 0b0111_1111) << (7 * size);
        offset += 1;
        size += 1;
    }

    result |= (charBuffer[offset] as i64) << (7 * size);

    (size + 1, result)
     */
    // auto tmp = charBuffer[offset];
    while (size < 8 && charBuffer[offset] >= 0x80) {
        result |= (static_cast<int64_t>(charBuffer[offset]) & 0x7f) << (7 * size);
        offset += 1;
        size += 1;
    }
    result |= (static_cast<int64_t>(charBuffer[offset]) & 0x7f) << (7 * size);
    return { result, size + 1 };
}

VLInt::VLInt(int64_t v)
    : value(v)
{
}
