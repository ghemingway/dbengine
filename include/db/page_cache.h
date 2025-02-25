// @author Graham Hemingway @copyright 2025 - All rights reserved

#ifndef PAGE_CACHE_H
#define PAGE_CACHE_H

#include "db/record.h"
#include <cstdint>
#include <fstream>

class Header;
class BTreePage;
class Page;

class PageCache {
public:
  PageCache(Header *header, std::fstream &fileStream);
  ~PageCache() = default;

  Page *fetchPage(uint32_t id);

private:
  Header *header;
  std::fstream &fileStream;
  Page *pages[1024];
};

class Scanner {
public:
  explicit Scanner(PageCache *cache, uint32_t pageId);
  ~Scanner() = default;

  bool hasNext() const;
  Record nextRecord();

private:
  PageCache *cache;
  BTreePage *page;
  uint32_t cell;
};

#endif // PAGE_CACHE_H
