#include <algorithm>
#include <engine/CollisionGrid.h>

#define CELLS_ACROSS 16
#define CELLS_DOWN 12
#define CELL_SIZE 50
CollisionGrid::CollisionGrid() {
	for (int i=0; i<192; i++) {
		cells[i].reserve(256); // Get 256 entities per cell by default. Maybe 1000 later.
	}
}

std::vector<unsigned short> CollisionGrid::insert_entity(Entity e) {
	// Insert Entity
	// Sort affected cells by entity ID
	std::vector<unsigned short> cell_ids = get_cells_within(e.x, e.y, 8);

	for (int i=0; i<cell_ids.size(); i++) {
		e.cells[i] = cell_ids.at(i);
	}
	for (int i=0; i<cell_ids.size(); i++) {
		cells[i].push_back(e);
	}

	return cell_ids;
}

void CollisionGrid::sort_cell(unsigned short cell_idx) {
}

void CollisionGrid::update_entity(Entity e) {
	// All sorts of fancy efficiency stuff
	// If we've just changed cell, check in direction behind us
}

// Assume x, y is the center of a radius circle
std::vector<unsigned short> CollisionGrid::get_cells_within(int x, int y, int radius) {

	std::vector<unsigned short> cell_ids;

	unsigned short cell_x = x / CELL_SIZE;
	unsigned short cell_y = y / CELL_SIZE;
	unsigned short base_cell_idx = cell_x + (cell_y*CELLS_ACROSS);

	cell_ids.push_back(base_cell_idx);

	int test_x[4] = { cell_x, cell_x + radius, cell_x - radius };


	return cell_ids;
}
