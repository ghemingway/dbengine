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
    std::variant<int64_t, double, bool, std::string, std::vector<unsigned char>> value;

    RecordField(RecordFieldType type, int8_t v)
        : type(type)
        , value(static_cast<int64_t>(v))
    {
    }
    RecordField(RecordFieldType type, std::string v)
        : type(type)
        , value(v)
    {
    }

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

    static auto readInt8(const unsigned char*) -> int64_t;
    static auto readInt16(const unsigned char*) -> int64_t;
    static auto readInt24(const unsigned char*) -> int64_t;
    static auto readInt32(const unsigned char*) -> int64_t;
    static auto readInt48(const unsigned char*) -> int64_t;
    static auto readInt64(const unsigned char*) -> int64_t;
    static auto readFloat64(const unsigned char*) -> double;
    static auto readBlob(const unsigned char*, size_t) -> std::vector<char>;
    static auto readString(const unsigned char*, size_t) -> std::string;
};

class Record {
public:
    explicit Record(const Cell&);

    auto operator[](size_t) const -> const RecordField&;

    static auto parseFields(const unsigned char* buffer) -> std::vector<RecordField>;

private:
    friend class Cell;

    const Cell& cell;
    std::vector<RecordField> fields;
};

#endif // RECORD_H
