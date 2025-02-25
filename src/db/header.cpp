// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/header.h"
#include "db/engine.h"
#include "util.h"

// https://blog.sylver.dev/build-your-own-sqlite-part-1-listing-tables
// https://www.sqlite.org/fileformat.html

constexpr std::string HEADER_PREFIX = "vandb format 1";
// constexpr uint32_t PAGE_MAX_SIZE = 65536;

Header::Header()
    : pageSize(4096), writeVersion(1), readVersion(1), resSpace(12),
      maxPayloadFrac(64), minPayloadFrac(32), leafFrac(32), changeCount(0),
      numPages(1), firstFree(0), cookie(2), schemaFormat(4), pageCacheSize(0),
      largestRoot(0), textEncoding(TextEncoding::UTF8), userVersion(0),
      incVacuum(0), appId(0), verValidFor(2), version(3043002) {}

/**
 * All bytes stored big-endian
 */
Header::Header(std::iostream &stream) : Header() {
  // Read header
  stream.read(reinterpret_cast<std::istream::char_type *>(this),
              sizeof(Header));
  // Prep magic for check
  if (std::string_view magic(this->magic, 16);
      !magic.starts_with(HEADER_PREFIX)) {
    const auto msg = "Invalid header: " + std::string(this->magic);
    throw std::runtime_error(msg);
  }

  // Adjust all multibyte values if on little-endian platform
  if constexpr (std::endian::native == std::endian::little) {
    pageSize = byteswap(pageSize);
    changeCount = byteswap(changeCount);
    numPages = byteswap(numPages);
    firstFree = byteswap(firstFree);
    numFree = byteswap(numFree);
    cookie = byteswap(cookie);
    schemaFormat = byteswap(schemaFormat);
    pageCacheSize = byteswap(pageCacheSize);
    largestRoot = byteswap(largestRoot);
    textEncoding = byteswap(textEncoding);
    userVersion = byteswap(userVersion);
    incVacuum = byteswap(incVacuum);
    appId = byteswap(appId);
    verValidFor = byteswap(verValidFor);
    version = byteswap(version);
  }
}

void Header::print(std::ostream &os) const {
  os << HEADER_PREFIX << std::endl;
  os << "\tpageSize: " << pageSize << std::endl;
  os << "\tnumPages: " << numPages << std::endl;
}

uint32_t Header::getPageSize() const { return pageSize; }