#include <algorithm>
#include <engine/CollisionGrid.h>

#define CELL_SIZE 50
#define CELLS_ACROSS 800/CELL_SIZE
#define CELLS_DOWN 600/CELL_SIZE

// Cell
CollisionCell::CollisionCell() {
	guy_count = 0;
	entity_count = 0;
}

void CollisionCell::insert_guy(Guy g) {
	guys[guy_count] = g;
	guy_count++;
}

int CollisionCell::get_guy_count() { return guy_count; }

Guy* CollisionCell::get_guy(int guy_idx) {
	return &guys[guy_idx];
}










// Grid
CollisionGrid::CollisionGrid() {
}

void CollisionGrid::insert_guy(Guy g) {
	int cell_id = g.x / CELL_SIZE + (g.y / CELL_SIZE) * CELLS_ACROSS;
	cells[cell_id].insert_guy(g);
};

int CollisionGrid::get_cell_count() { return CELLS_ACROSS*CELLS_DOWN; }

CollisionCell* CollisionGrid::get_cell(int cell_idx) { return &cells[cell_idx]; }

Guy* CollisionGrid::get_guy(int cell_idx, int guy_idx) {
	return cells[cell_idx].get_guy(guy_idx);
}

