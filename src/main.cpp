// @author Graham Hemingway @copyright 2025 - All rights reserved
#include "db/vandb.h"
#include <filesystem>
#include <fstream>
#include <iostream>

auto main(int argc, char** argv) -> int
{
    std::cout << "VanDB Reader v" << VERSION_STRING << std::endl;
    try {
        if (argc != 2)
            throw std::invalid_argument("Wrong number of arguments");

        const VanDB db(argv[1]);
        db.displayTables(std::cout);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
