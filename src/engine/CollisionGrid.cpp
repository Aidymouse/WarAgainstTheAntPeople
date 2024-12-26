#include <algorithm>
#include <engine/CollisionGrid.h>

#define CELLS_ACROSS 16
#define CELLS_DOWN 12
#define CELL_SIZE 50

// Cell
CollisionCell::CollisionCell() {
	guy_count = 0;
	entity_count = 0;
}

void CollisionCell::insert_guy(Guy g) {
	guys[guy_count] = g;
	guy_count++;
}

// Grid
CollisionGrid::CollisionGrid() {
}

