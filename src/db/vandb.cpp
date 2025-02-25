// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/vandb.h"
#include "db/btree.h"
#include "db/engine.h"
#include "db/header.h"
#include "db/page_cache.h"
#include "db/scanner.h"

VanDB::VanDB(const std::string& path)
    : filePath(path)
    , fileStream()
    , header(nullptr)
    , pageCache(nullptr)
{
    // Does database file exist
    if (!std::filesystem::exists(filePath))
        throw std::runtime_error("file does not exist");
    // Try to open file stream
    fileStream.open(filePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!fileStream.is_open())
        throw std::runtime_error("file cannot be opened");

    // Open DB file
    header = new Header(fileStream);
    // Establish the page cache
    pageCache = new PageCache(header, fileStream);
}

void VanDB::displayTables(std::ostream& os) const
{
    if constexpr (DEBUG)
        header->print(os);
    // Fetch the first page (ie master table)
    Scanner scanner(pageCache, 1);
    // Print the details
    while (scanner.hasNext()) {
        auto record = scanner.nextRecord();
        auto valueType = record[0].toString();
        auto tableName = record[1].toString();
        auto value = record[3].toInt8();
        auto sql = record[4].toString();
        os << "\t" << valueType << ": " << tableName << ": " << sql << std::endl;
    }
}

VanDB::~VanDB()
{
    // Clean up
    delete header;
    delete pageCache;

    fileStream.close();
}
