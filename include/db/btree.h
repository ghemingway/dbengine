// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef BTREE_H
#define BTREE_H

#include "./page.h"
#include "./record.h"
#include <cstdint>
#include <istream>
#include <vector>

class Cell;

enum BtreePageType : uint8_t {
    IndexInterior = 2,
    TableInterior = 5,
    IndexLeaf = 10,
    TableLeaf = 13
};

struct BTreeHeader {
    BtreePageType type;
    uint16_t freeStart;
    uint16_t numCells;
    uint16_t cellStart;
    uint8_t numFragFree;
    uint32_t pageNum;
};

class BTreePage : public Page {
public:
    explicit BTreePage(const unsigned char* pageBuffer, bool pageZero);
    ~BTreePage() override;

    static BTreePage* read(std::iostream&, uint32_t, bool pageZero);

    [[nodiscard]] auto numCells() const -> uint32_t;
    auto record(uint32_t index) -> Record&;

protected:
    void printHeader(std::ostream& os) const;
    void parseCells(const unsigned char* pageBuffer, bool pageZero);

    BTreeHeader header {};
    std::vector<Cell*> cells;
};

class BTreeTableLeaf final : public BTreePage {
public:
    explicit BTreeTableLeaf(const unsigned char*, uint32_t, bool pageZero);
    void print(std::ostream&) const override;
};

class BTreeTableInterior final : public BTreePage {
public:
    explicit BTreeTableInterior(const unsigned char*, uint32_t, bool pageZero);
    void print(std::ostream&) const override;
};

class BTreeIndexLeaf final : public BTreePage {
public:
    explicit BTreeIndexLeaf(const unsigned char*, uint32_t, bool pageZero);
    void print(std::ostream&) const override;
};

class BTreeIndexInterior final : public BTreePage {
public:
    explicit BTreeIndexInterior(const unsigned char*, uint32_t, bool pageZero);
    void print(std::ostream&) const override;
};

#endif // BTREE_H
