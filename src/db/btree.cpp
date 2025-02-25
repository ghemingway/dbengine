// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/btree.h"
#include "db/cell.h"
#include "db/engine.h"
#include "util.h"
#include <iostream>

BTreePage* BTreePage::read(std::iostream& stream, const uint32_t pageSize, bool pageZero)
{
    char buffer[pageSize];
    stream.read(buffer, pageSize);
    switch (const auto* header = reinterpret_cast<BTreeHeader*>(buffer); header->type) {
    case TableLeaf:
        return new BTreeTableLeaf(reinterpret_cast<unsigned char*>(buffer), pageSize, pageZero);
    case TableInterior:
        return new BTreeTableInterior(reinterpret_cast<unsigned char*>(buffer), pageSize, pageZero);
    case IndexLeaf:
        return new BTreeIndexLeaf(reinterpret_cast<unsigned char*>(buffer), pageSize, pageZero);
    case IndexInterior:
        return new BTreeIndexInterior(reinterpret_cast<unsigned char*>(buffer), pageSize, pageZero);

    default:
        throw std::runtime_error("BTreePage::read: unknown page type");
    }
}

BTreePage::BTreePage(const unsigned char* pageBuffer, bool pageZero)
    : Page(0x0D)
    , header {}
    , cells()
{
    // Copy in the header data
    // std::memcpy(&header, pageBuffer, sizeof(BTreeHeader));
    std::memcpy(&header.type, pageBuffer, 1);
    std::memcpy(&header.freeStart, pageBuffer + 1, 2);
    std::memcpy(&header.numCells, pageBuffer + 3, 2);
    std::memcpy(&header.cellStart, pageBuffer + 5, 2);
    std::memcpy(&header.numFragFree, pageBuffer + 7, 1);
    std::memcpy(&header.pageNum, pageBuffer + 8, 4);
    pageType = header.type;
    // Adjust all multibyte values if on little-endian platform
    if constexpr (std::endian::native == std::endian::little) {
        header.freeStart = byteswap(header.freeStart);
        header.numCells = byteswap(header.numCells);
        header.cellStart = byteswap(header.cellStart);
        header.pageNum = byteswap(header.pageNum);
    }
    // Parse the cells
    parseCells(pageBuffer, pageZero);
}

BTreePage::~BTreePage()
{
    for (const auto& cell : cells) {
        delete cell;
    }
}

uint32_t BTreePage::numCells() const
{
    return cells.size();
}

Record& BTreePage::record(uint32_t index)
{
    auto cell = cells[index];
    return cell->toRecord();
}

void BTreePage::parseCells(const unsigned char* pageBuffer, const bool pageZero)
{
    // Parse cells
    uint16_t cellOffset;
    for (uint32_t i = 0; i < header.numCells; ++i) {
        const auto offset = i * 2 + (header.type == BtreePageType::TableInterior ? 12 : 8);
        std::memcpy(&cellOffset, pageBuffer + offset, 2);
        if constexpr (std::endian::native == std::endian::little) {
            cellOffset = byteswap(cellOffset);
        }
        // Adjust if this is page zero (i.e. has DB header)
        cellOffset = pageZero ? cellOffset - 100 : cellOffset;
        if constexpr (DEBUG)
            std::cout << "Cell: " << cellOffset << std::endl;
        cells.emplace_back(new Cell(pageBuffer + cellOffset, header.type));
    }
}

void BTreePage::printHeader(std::ostream& os) const
{
    os << "\tFree Start: " << header.freeStart << std::endl;
    os << "\tNum Cells: " << header.numCells << std::endl;
    os << "\tCell Start: " << header.cellStart << std::endl;
    os << "\tFrag Start: " << header.numFragFree << std::endl;
}

BTreeTableLeaf::BTreeTableLeaf(const unsigned char* pageBuffer, const uint32_t, bool pageZero)
    : BTreePage(pageBuffer, pageZero)
{
}

void BTreeTableLeaf::print(std::ostream& os) const
{
    os << "BTreeTableLeaf::BTreeTableLeaf()" << std::endl;
    printHeader(os);
    // Iterate over every record in the page
    for (const auto& cell : cells) { }
}

BTreeTableInterior::BTreeTableInterior(
    const unsigned char* pageBuffer, const uint32_t, bool pageZero)
    : BTreePage(pageBuffer, pageZero)
{
    std::cout << "BTreeTableInterior" << std::endl;
    std::cout << "\tNum Cells: " << header.numCells << std::endl;
    std::cout << "\tCell Start: " << header.cellStart << std::endl;
}

void BTreeTableInterior::print(std::ostream&) const
{
    std::cout << "BTreeTableInterior::BTreeTableInterior()" << std::endl;
}

BTreeIndexLeaf::BTreeIndexLeaf(const unsigned char* pageBuffer, const uint32_t, bool pageZero)
    : BTreePage(pageBuffer, pageZero)
{
    std::cout << "BTreeIndexLeaf" << std::endl;
    std::cout << "\tNum Cells: " << header.numCells << std::endl;
    std::cout << "\tCell Start: " << header.cellStart << std::endl;
}

void BTreeIndexLeaf::print(std::ostream&) const
{
    std::cout << "BTreeIndexLeaf::BTreeIndexLeaf()" << std::endl;
}

BTreeIndexInterior::BTreeIndexInterior(
    const unsigned char* pageBuffer, const uint32_t, bool pageZero)
    : BTreePage(pageBuffer, pageZero)
{
    std::cout << "BTreeIndexInterior" << std::endl;
    std::cout << "\tNum Cells: " << header.numCells << std::endl;
    std::cout << "\tCell Start: " << header.cellStart << std::endl;
}

void BTreeIndexInterior::print(std::ostream&) const
{
    std::cout << "BTreeIndexInterior::BTreeIndexInterior()" << std::endl;
}