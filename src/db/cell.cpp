// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/cell.h"
#include "db/engine.h"
#include "db/record.h"
#include "db/vl_int.h"
#include <iostream>

Cell::Cell(const char *cellBuffer, const BtreePageType type)
    : id(0), record(*this) {
  // Size of cell data
  uint32_t offset = 0;
  auto [cellSize, cellSizeB] = VarInt::parse(cellBuffer);
  offset += cellSizeB;

  // Different types define cell header fields
  if (type == BtreePageType::TableLeaf) {
    // Get Record ID
    auto [cellId, cellIdB] = VarInt::parse(cellBuffer + offset);
    offset += cellIdB;
    id = cellId;
    if constexpr (DEBUG)
      std::cout << "\tID: " << id << std::endl;

    record.fields = Record::parseFields(cellBuffer + offset);
    /*
      // Header size in bytes
      auto [headerSize, headerSizeB] = VarInt::parse(cellBuffer + offset);
      offset += headerSizeB;
      std::cout << "\tHeader Size: " << headerSize << std::endl;

      // Offset of where next value is stored
      uint16_t valuesOffset = cellSizeB + cellIdB + headerSize;
      // Read each field type + process each value
      for (auto i = 0; i < headerSize - headerSizeB;) {
        auto [fieldType, readB] = VarInt::parse(cellBuffer + offset + i);

        // 8-bit signed integer
        if (fieldType == RecordFieldType::Null) {
          std::cout << "\tNull field" << std::endl;
          fields.emplace_back(RecordFieldType::Null, 0);
        } else if (fieldType == RecordFieldType::I8) {
          fields.emplace_back(RecordFieldType::I8, valuesOffset);
          valuesOffset += 1;
        } else if (fieldType == RecordFieldType::I16) {
          fields.emplace_back(RecordFieldType::I16, valuesOffset);
          valuesOffset += 2;
        } else if (fieldType == RecordFieldType::I24) {
          fields.emplace_back(RecordFieldType::I24, valuesOffset);
          valuesOffset += 3;
        } else if (fieldType == RecordFieldType::I32) {
          fields.emplace_back(RecordFieldType::I32, valuesOffset);
          valuesOffset += 4;
        } else if (fieldType == RecordFieldType::I48) {
          fields.emplace_back(RecordFieldType::I48, valuesOffset);
          valuesOffset += 6;
        } else if (fieldType == RecordFieldType::I64) {
          fields.emplace_back(RecordFieldType::I64, valuesOffset);
          valuesOffset += 8;
        } else if (fieldType == RecordFieldType::Float) {
          fields.emplace_back(RecordFieldType::Float, valuesOffset);
          valuesOffset += 8;
        } else if (fieldType == RecordFieldType::Zero) {
          fields.emplace_back(RecordFieldType::Zero, 0);
        } else if (fieldType == RecordFieldType::One) {
          fields.emplace_back(RecordFieldType::One, 0);
        } else if (fieldType >= 12 && fieldType % 2 == 0) {
          const auto blobLen = (fieldType - 12) / 2;
          // TODO: Need to capture blob length too
          fields.emplace_back(RecordFieldType::Blob, valuesOffset);
          valuesOffset += blobLen;
        } else if (fieldType >= 12 && fieldType % 2 == 1) {
          const auto strLen = (fieldType - 13) / 2;
          // TODO: Need to capture string length too
          fields.emplace_back(RecordFieldType::String, valuesOffset);
          // std::string str =
          //     RecordField::readString(cellBuffer + valuesOffset, strLen);
          // std::cout << "\tString(" << valuesOffset << "): " << str <<
          // std::endl;
          valuesOffset += strLen;
        } else {
          std::cout << fieldType << ", " << static_cast<int>(readB) <<
      std::endl; throw std::runtime_error("Unknown field type");
        }
        i += readB;
      }
    */
  } else if (type == BtreePageType::TableInterior) {
  } else if (type == BtreePageType::IndexLeaf) {
  } else if (type == BtreePageType::IndexInterior) {
  } else {
    throw std::runtime_error("Unknown cell type");
  }
}
//
// const RecordField &Cell::field(const size_t index) const {
//   if (index >= fields.size())
//     throw std::runtime_error("Index out of bounds");
//   return fields.at(index);
// }

Record &Cell::toRecord() { return record; }
