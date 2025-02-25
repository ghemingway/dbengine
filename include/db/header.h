// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef DB_HEADER_H
#define DB_HEADER_H

#include <cstdint>
#include <iostream>

class Header {
public:
    /**
     * Primary constructor
     * @param stream - byte stream to read/write data from/to
     */
    explicit Header(std::iostream& stream);

    /**
     * Print out details of the header
     * @return stringified version of the header
     */
    void print(std::ostream&) const;

    uint32_t getPageSize() const;

private:
    friend class VanDB;

    /**
     * Default constructor
     */
    Header();

    char magic[16] {}; // Must be magic string with null termination
    uint16_t pageSize {}; // Must be a power of two between 512 and 32768 inclusive,
                          // or the value 1 representing a page size of 65536.
    uint8_t writeVersion {}; // 1 for legacy; 2 for WAL.
    uint8_t readVersion {}; // 1 for legacy; 2 for WAL.
    uint8_t resSpace {}; // bytes of unused "reserved" space at the end of each
                         // page. Usually 0.
    uint8_t maxPayloadFrac {}; // Maximum embedded payload fraction. Must be 64.
    uint8_t minPayloadFrac {}; // Minimum embedded payload fraction. Must be 32.
    uint8_t leafFrac {}; // Leaf payload fraction. Must be 32.
    uint32_t changeCount {}; // File change counter.
    uint32_t numPages {}; // Size of the database file in pages. The "in-header
                          // database size".
    uint32_t firstFree {}; // Page number of the first freelist trunk page.
    uint32_t numFree {}; // Total number of freelist pages.
    uint32_t cookie {}; // The schema cookie.
    uint32_t schemaFormat {}; // The schema format number. Supported schema formats
                              // are 1, 2, 3, and 4.
    uint32_t pageCacheSize {}; // Default page cache size.
    uint32_t largestRoot {}; // The page number of the largest root b-tree page
                             // when in auto-vacuum or incremental-vacuum modes, or
                             // zero otherwise.
    uint32_t textEncoding {}; // The database text encoding. A value of 1 means UTF-8. A
                              // value of 2 means UTF-16le. A value of 3 means UTF-16be.
    uint32_t userVersion {}; // The "user version" as read and set by the
                             // user_version pragma.
    uint32_t incVacuum {}; // True (non-zero) for incremental-vacuum mode. False
                           // (zero) otherwise.
    uint32_t appId {}; // The "Application ID" set by PRAGMA application_id.
    char reservedExp[20] {}; // Reserved for expansion. Must be zero.
    uint32_t verValidFor {}; // The version-valid-for number.
    uint32_t version {}; // SQLITE_VERSION_NUMBER
};

#endif // DB_HEADER_H
