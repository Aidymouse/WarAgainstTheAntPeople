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
	void insert_guy(Guy g);
	void insert_entity(Entity e);
};

class CollisionGrid {
	CollisionCell cells[NUM_CELLS];

public:
	CollisionGrid();
	void insert_guy(Guy g);
	void insert_entity(Entity e); 
};
