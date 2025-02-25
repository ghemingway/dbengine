// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef PAGE_CACHE_H
#define PAGE_CACHE_H

#include <cstdint>
#include <fstream>

class Header;
class Page;

/**
 *
 */
class PageCache {
public:
    PageCache(Header* header, std::fstream& fileStream);
    PageCache(const PageCache&) = delete;
    ~PageCache() = default;

    auto operator=(const PageCache&) -> PageCache& = delete;

    /**
     *
     * @param id
     * @return
     */
    auto fetchPage(uint32_t id) -> Page*;

private:
    Header* header;
    std::fstream& fileStream;
    std::array<Page*, 1024> pages;
};

#endif // PAGE_CACHE_H
