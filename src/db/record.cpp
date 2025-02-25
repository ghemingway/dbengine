// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/record.h"
#include "db/engine.h"
#include "db/vl_int.h"
#include "util.h"
#include <bit>
#include <iostream>
#include <utility>

#include "db/cell.h"

Record::Record(const Cell& cell)
    : cell(cell)
    , fields {}
{
}

auto RecordField::toInt8() const -> int8_t
{
    return std::get<int64_t>(value);
}

int16_t RecordField::toInt16() const
{
    return 0;
}

int32_t RecordField::toInt24() const
{
    return 0;
}

int32_t RecordField::toInt32() const
{
    return 0;
}

int64_t RecordField::toInt48() const
{
    return 0;
}

int64_t RecordField::toInt64() const
{
    return 0;
}

double RecordField::toFloat64() const
{
    return 0;
}

std::vector<char> RecordField::toBlob() const
{
    return {};
}

auto RecordField::toString() const -> std::string
{
    return std::get<std::string>(value);
}

auto Record::parseFields(const unsigned char* buffer) -> std::vector<RecordField>
{
    uint32_t offset = 0;
    std::vector<RecordField> fields;

    // Header size in bytes
    auto [headerSize, headerSizeB] = VLInt::parse(buffer + offset);
    offset += headerSizeB;
    if constexpr (DEBUG)
        std::cout << "\tHeader Size: " << headerSize << std::endl;

    // Offset of where next value is stored
    uint16_t valuesOffset = headerSize;
    // Read each field type + process each value
    for (auto i = 0; i < headerSize - headerSizeB;) {
        auto [fieldType, readB] = VLInt::parse(buffer + offset + i);

        // 8-bit signed integer
        if (fieldType == RecordFieldType::Null) {
            std::cout << "\tNull field" << std::endl;
            RecordField field(RecordFieldType::Null, 0);
            fields.emplace_back(field);
        } else if (fieldType == RecordFieldType::I8) {
            fields.emplace_back(RecordFieldType::I8, RecordField::readInt8(buffer + valuesOffset));
            valuesOffset += 1;
        } else if (fieldType == RecordFieldType::I16) {
            fields.emplace_back(
                RecordFieldType::I16, RecordField::readInt16(buffer + valuesOffset));
            valuesOffset += 2;
        } else if (fieldType == RecordFieldType::I24) {
            fields.emplace_back(
                RecordFieldType::I24, RecordField::readInt24(buffer + valuesOffset));
            valuesOffset += 3;
        } else if (fieldType == RecordFieldType::I32) {
            fields.emplace_back(
                RecordFieldType::I32, RecordField::readInt32(buffer + valuesOffset));
            valuesOffset += 4;
        } else if (fieldType == RecordFieldType::I48) {
            fields.emplace_back(
                RecordFieldType::I48, RecordField::readInt48(buffer + valuesOffset));
            valuesOffset += 6;
        } else if (fieldType == RecordFieldType::I64) {
            fields.emplace_back(
                RecordFieldType::I64, RecordField::readInt64(buffer + valuesOffset));
            valuesOffset += 8;
        } else if (fieldType == RecordFieldType::Float) {
            fields.emplace_back(
                RecordFieldType::Float, RecordField::readFloat64(buffer + valuesOffset));
            valuesOffset += 8;
        } else if (fieldType == RecordFieldType::Zero) {
            fields.emplace_back(RecordFieldType::Zero, false);
        } else if (fieldType == RecordFieldType::One) {
            fields.emplace_back(RecordFieldType::One, true);
        } else if (fieldType >= 12 && fieldType % 2 == 0) {
            const auto blobLen = (fieldType - 12) / 2;
            // TODO Fix
            // fields.emplace_back(RecordFieldType::Blob, buffer + valuesOffset,
            // blobLen);
            valuesOffset += blobLen;
        } else if (fieldType >= 12 && fieldType % 2 == 1) {
            const uint32_t strLen = (fieldType - 13) / 2;
            fields.emplace_back(
                RecordFieldType::String, RecordField::readString(buffer + valuesOffset, strLen));
            valuesOffset += strLen;
        } else {
            std::cout << fieldType << ", " << static_cast<int>(readB) << std::endl;
            throw std::runtime_error("Unknown field type");
        }
        i += readB;
    }

    return fields;
}

auto RecordField::readInt8(const unsigned char* buffer) -> int64_t
{
    int8_t result;
    std::memcpy(&result, buffer, sizeof(result));
    return result;
}

auto RecordField::readInt16(const unsigned char* buffer) -> int64_t
{
    int16_t result;
    std::memcpy(&result, buffer, sizeof(result));
    if constexpr (std::endian::native == std::endian::little) {
        result = byteswap(result);
    }
    return result;
}

auto RecordField::readInt24(const unsigned char*) -> int64_t
{
    // TODO: Complete this
    throw std::runtime_error("Not implemented");
}

auto RecordField::readInt32(const unsigned char* buffer) -> int64_t
{
    int32_t result;
    std::memcpy(&result, buffer, sizeof(result));
    if constexpr (std::endian::native == std::endian::little) {
        result = byteswap(result);
    }
    return result;
}

auto RecordField::readInt48(const unsigned char*) -> int64_t
{
    // TODO: Complete this
    throw std::runtime_error("Not implemented");
}

auto RecordField::readInt64(const unsigned char* buffer) -> int64_t
{
    int64_t result;
    std::memcpy(&result, buffer, sizeof(result));
    if constexpr (std::endian::native == std::endian::little) {
        result = byteswap(result);
    }
    return result;
}

auto RecordField::readFloat64(const unsigned char*) -> double
{
    // TODO: Complete this
    throw std::runtime_error("Not implemented");
}

auto RecordField::readString(const unsigned char* buffer, const size_t length) -> std::string
{
    std::string str(reinterpret_cast<const char*>(buffer), length);
    return str;
}

auto Record::operator[](const size_t index) const -> const RecordField&
{
    return fields.at(index);
}
