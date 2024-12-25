#pragma once

#include <entity/Entity.h>
#include <vector>

typedef unsigned short cell_id;

#define ENTS_PER_CELL 256
#define NUM_CELLS 16*18
class CollisionGrid {
	Entity cells[ENTS_PER_CELL][NUM_CELLS];
	int cell_counts[NUM_CELLS] = {0};

public:
	CollisionGrid();
	void insert_entity(Entity e); 
	void remove_entity(Entity e);
	void update_entity(Entity e);

	Entity* get_entities(cell_id id);
	int get_count(cell_id id);
};
