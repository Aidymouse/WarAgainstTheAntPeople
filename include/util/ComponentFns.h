#pragma once

#include <ecs/ECS.hpp>
#include <engine/CollisionGrid.h>

namespace ComponentFns {
	void clean_remove(Entity ent, ECS* ecs);
	void clean_remove(Entity ent, ECS* ecs, CollisionGrid *grid);

	/** Hivemind */
	void remove_hivemind(Entity ent, ECS *ecs);

	/** Carry */
	//void stop_being_carryable(ECS *ecs, Entity ent);

	/** Buld */
	void advance_build_stage(ECS *ecs, Buildable *b, Entity ent);
}
