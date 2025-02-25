// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/scanner.h"
#include "db/btree.h"
#include "db/page_cache.h"

Scanner::Scanner(PageCache* cache, uint32_t pageId)
    : cache(cache)
    , page(nullptr)
    , cell(0)
{
    page = dynamic_cast<BTreePage*>(cache->fetchPage(pageId));
    if (page == nullptr)
        throw std::runtime_error("page not found");
}

auto Scanner::hasNext() const -> bool
{
    return page && cell < page->numCells();
}

auto Scanner::nextRecord() -> Record&
{
    return page->record(cell++);
}