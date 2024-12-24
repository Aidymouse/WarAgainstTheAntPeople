#pragma once

#include <entity/Entity.h>
#include <vector>

class CollisionGrid {
	std::vector<Entity> cells[192];	// Keeping cells sorted might be the best move in terms of caching

public:
	CollisionGrid();
	std::vector<unsigned short> insert_entity(Entity e); // Returns cells added to
	void remove_entity(Entity e);
	void update_entity(Entity e);
	void sort_cell(unsigned short cell_idx);
	std::vector<unsigned short> get_cells_within(int x, int y, int radius);
};
