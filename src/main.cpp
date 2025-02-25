// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/engine.h"
#include <filesystem>
#include <fstream>
#include <iostream>

#include "db/vandb.h"

int main() {
  std::cout << "VanDB Reader v" << VERSION_STRING << std::endl;
  try {
    VanDB db("../tests/data/test.db");
    db.displayTables(std::cout);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
