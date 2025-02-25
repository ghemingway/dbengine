// @author Graham Hemingway @copyright 2025 - All rights reserved
#ifndef CELL_H
#define CELL_H

#include "./btree.h"
#include "./record.h"

class Cell {
public:
  Cell(const char *, BtreePageType);

  Record &toRecord();

private:
  int64_t id;
  // const char *data;
  Record record;
};

#endif // CELL_H
