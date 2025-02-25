// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/page_cache.h"
#include "db/btree.h"
#include "db/header.h"
#include "db/page.h"

PageCache::PageCache(Header *header, std::fstream &fileStream)
    : header(header), fileStream(fileStream), pages{} {}

Page *PageCache::fetchPage(const uint32_t id) {
  // Do we already have the page
  if (pages[id - 1])
    return pages[id - 1];

  Page *page = nullptr;
  if (id == 1) {
    // Start reading right after the DB header
    fileStream.seekg(sizeof(Header), std::ios::beg);
    // Store into the cache and return
    pages[0] = page = BTreePage::read(
        fileStream, header->getPageSize() - sizeof(Header), true);
  } else {
    const auto offset = header->getPageSize() * (id - 1);
    // Start reading right after the DB header
    fileStream.seekg(offset, std::ios::beg);
    pages[id - 1] = page =
        BTreePage::read(fileStream, header->getPageSize(), false);
  }
  return page;
}

Scanner::Scanner(PageCache *cache, uint32_t pageId)
    : cache(cache), page(nullptr), cell(0) {
  page = dynamic_cast<BTreePage *>(cache->fetchPage(pageId));
  if (page == nullptr)
    throw std::runtime_error("page not found");
}

bool Scanner::hasNext() const { return page && cell < page->numCells(); }

Record Scanner::nextRecord() { return page->record(cell++); }