// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef PAGE_H
#define PAGE_H
#include <cstdint>
#include <ostream>

class Page {
public:
    explicit Page(uint32_t type);
    virtual ~Page() = default;

    virtual void print(std::ostream&) const = 0;

protected:
    uint32_t pageType;

private:
};

#endif // PAGE_H
