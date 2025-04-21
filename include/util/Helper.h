#pragma once

#include "engine/CollisionGrid.h"
#include <set>

namespace Helper {
void cout_set(std::set<int> *s);
void cout_cell_ids(std::set<collision_cell_id> *s);
bool quicksort(int* a, int start, int end);
} // namespace Helper
