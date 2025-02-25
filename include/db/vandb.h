// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef DB_H
#define DB_H

#include "db/engine.h"
#include <filesystem>
#include <fstream>

class Header;
class PageCache;

/**
 *
 */
class VanDB {
public:
    explicit VanDB(const std::string& path = "");
    VanDB(const VanDB&) = delete;
    ~VanDB();

    VanDB& operator=(const VanDB&) = delete;

    /**
     *
     */
    void displayTables(std::ostream&) const;

private:
    std::filesystem::path filePath;
    std::fstream fileStream;
    Header* header;
    PageCache* pageCache;
};

#endif // DB_H
