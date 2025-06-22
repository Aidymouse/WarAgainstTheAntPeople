#include "engine/CollisionGrid.h"
#include <functional>
#include <iostream>
#include <util/Helper.h>

void Helper::cout_set(std::set<int> *s) {
  if (s->size() == 0) {
    std::cout << "Empty Set" << std::endl;
    return;
  }

  for (auto i = s->begin(); i != s->end(); i++) {
    int num = (int)*i;
    std::cout << num << ", ";
  }

  std::cout << std::endl;
}

void Helper::cout_cell_ids(std::set<ColCellId> *s) {
  for (auto i = s->begin(); i != s->end(); i++) {
    ColCellId id = (ColCellId)*i;
    std::cout << "(" << (id >> 4) << ", " << (id - ((id >> 4) << 4)) << "), ";
  }
  std::cout << std::endl;
}

void Helper::cout_arr(int *a, int len) {
  std::cout << "[";
  for (int i = 0; i < len; i++) {
    std::cout << a[i];
    if (i != len - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}
