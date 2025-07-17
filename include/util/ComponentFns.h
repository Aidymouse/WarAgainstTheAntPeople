#pragma once

#include <ECS/ecs.hpp>

namespace ComponentFns {
	void clean_remove(Entity ent, ECS* ecs);
	void clean_remove(Entity ent, ECS* ecs, CollisionGrid *grid);

	/** Hivemind */
	void dissolve_hivemind(ECS *ecs, Entity ent);

	/** Carry */
	//void stop_being_carryable(ECS *ecs, Entity ent);

	/** Buld */
	void advance_build_stage(ECS *ecs, Buildable *b, Entity ent);
}
