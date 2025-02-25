// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>

class Cell;

enum RecordFieldType {
  Null = 0,
  I8,
  I16,
  I24,
  I32,
  I48,
  I64,
  Float,
  Zero,
  One,
  String,
  Blob,
};

struct RecordField {
  RecordFieldType type;
  std::variant<int64_t, double, bool, std::string, std::vector<unsigned char>>
      value;

  RecordField(RecordFieldType type, int8_t v)
      : type(type), value(static_cast<int64_t>(v)) {}
  RecordField(RecordFieldType type, std::string v) : type(type), value(v) {}

  int8_t toInt8() const;
  int16_t toInt16() const;
  int32_t toInt24() const;
  int32_t toInt32() const;
  int64_t toInt48() const;
  int64_t toInt64() const;
  double toFloat64() const;
  bool toBool() const;
  std::vector<char> toBlob() const;
  std::string toString() const;

  static int8_t readInt8(const char *);
  static int16_t readInt16(const char *);
  static int32_t readInt24(const char *);
  static int32_t readInt32(const char *);
  static int64_t readInt48(const char *);
  static int64_t readInt64(const char *);
  static double readFloat64(const char *);
  static std::vector<char> readBlob(const char *, size_t);
  static std::string readString(const char *, size_t);
};

class Record {
public:
  explicit Record(const Cell &);

  const RecordField &operator[](size_t) const;

  static std::vector<RecordField> parseFields(const char *buffer);

private:
  friend class Cell;

  const Cell &cell;
  std::vector<RecordField> fields;
};

#endif // RECORD_H
