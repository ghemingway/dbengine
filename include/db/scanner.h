// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef SCANNER_H
#define SCANNER_H

#include "db/record.h"

class BTreePage;
class PageCache;

/**
 *
 */
class Scanner {
public:
    explicit Scanner(PageCache* cache, uint32_t pageId);
    ~Scanner() = default;

    [[nodiscard]] auto hasNext() const -> bool;
    auto nextRecord() -> Record&;

private:
    PageCache* cache;
    BTreePage* page;
    uint32_t cell;
};

#endif // SCANNER_H
