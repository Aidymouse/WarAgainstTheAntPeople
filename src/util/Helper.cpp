#include "engine/CollisionGrid.h"
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

void Helper::cout_cell_ids(std::set<collision_cell_id> *s) {
  for (auto i = s->begin(); i != s->end(); i++) {
    collision_cell_id id = (collision_cell_id)*i;
    std::cout << "(" << (id >> 4) << ", " << (id - ((id >> 4) << 4)) << "), ";
  }
  std::cout << std::endl;
}
