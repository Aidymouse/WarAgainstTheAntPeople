#include <algorithm>
#include <engine/CollisionGrid.h>

#define CELLS_ACROSS 16
#define CELLS_DOWN 12
#define CELL_SIZE 50
CollisionGrid::CollisionGrid() {
}

void CollisionGrid::insert_entity(Entity e) {
	int base_cell_x = e.x / CELL_SIZE;
	int base_cell_y = e.y / CELL_SIZE;

	int cell_id = base_cell_x + base_cell_y * CELLS_ACROSS;

	cells[cell_id][cell_counts[cell_id]] = e;
	cell_counts[cell_id]++;
}


void CollisionGrid::update_entity(Entity e) {
	// All sorts of fancy efficiency stuff
	// If we've just changed cell, check in direction behind us
}

Entity* CollisionGrid::get_entities(cell_id id) {
	return cells[id];
}

int CollisionGrid::get_count(cell_id id) {
	return cell_counts[id];
}

// Assume x, y is the center of a radius circle
/*std::vector<unsigned short> CollisionGrid::get_cells_within(int x, int y, int radius) {*/
/**/
/*	std::vector<unsigned short> cell_ids;*/
/**/
/*	unsigned short cell_x = x / CELL_SIZE;*/
/*	unsigned short cell_y = y / CELL_SIZE;*/
/*	unsigned short base_cell_idx = cell_x + (cell_y*CELLS_ACROSS);*/
/**/
/*	cell_ids.push_back(base_cell_idx);*/
/**/
/*	int test_x[4] = { cell_x, cell_x + radius, cell_x - radius };*/
/**/
/**/
/*	return cell_ids;*/
/*}*/
