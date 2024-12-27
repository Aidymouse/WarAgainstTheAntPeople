#pragma once

#include <entity/Entity.h>
#include <entity/Guy.h>

typedef char cell_id;

#define MAX_ENTS 256 
#define NUM_CELLS 16*18

class CollisionCell {
	Guy guys[250];
	Entity* other_entites[256];

	int guy_count;
	int entity_count;
public:
	CollisionCell();
	void insert_guy(Guy g);
	void insert_entity(Entity e);

	int get_guy_count();
	int get_entity_count();
};

class CollisionGrid {
	CollisionCell cells[NUM_CELLS];

public:
	CollisionGrid();
	void insert_guy(Guy g);
	void insert_entity(Entity e); 

	int get_cell_count();
	CollisionCell* get_cell(int cell_idx);
};
