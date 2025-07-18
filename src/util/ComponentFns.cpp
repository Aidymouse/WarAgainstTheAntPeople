#include <util/ComponentFns.h>
#include <components/Components.hpp>
#include <components/HivemindComponents.hpp>

/** All Purpose */

// Removes an entity making provision for all noodley interconnected component bits
void ComponentFns::clean_remove(Entity ent, ECS *ecs) {
	if (ecs->entity_has_component<hv_Brain>(ent)) { ComponentFns::remove_hivemind(ent, ecs); }
	ecs->remove_entity(ent);
}

void ComponentFns::clean_remove(Entity ent, ECS *ecs, CollisionGrid *grid) {
	grid->remove_entity(ent);
	ComponentFns::clean_remove(ent, ecs);
}


/** Hivemind */
void ComponentFns::remove_hivemind(Entity ent, ECS *ecs) {
	hv_Brain *hv = ecs->get_component_for_entity<hv_Brain>(ent);

	for (int e=0; e<hv->num_entities; e++) {
		ecs->remove_component_from_entity<hv_Participant>(hv->entities[e]);
	}
	
	ecs->remove_component_from_entity<hv_Brain>(ent);
}
/*
// Carry system performs it's own cleanup but we might not need to do that
void ComponentFns::stop_being_carryable(ECS *ecs, Entity ent) {
  Carryable *c = ecs->get_component_for_entity<Carryable>(ent);

  for (int ci = c->carriers_count - 1; ci > 0; ci++) {
  }
}
*/

//void create_buildsite(ECS *ecs) {}

/** Build */
void ComponentFns::advance_build_stage(ECS *ecs, Buildable *b, Entity ent){
	//b->cur_build_points -= b->points_required[b->cur_stage];
	b->cur_stage+=1;
	b->cur_build_points = 0;

	if (ecs->entity_has_component<Visible>(ent)) {
		Visible *v = ecs->get_component_for_entity<Visible>(ent);
		v->frame = b->stage_frames[b->cur_stage];
	}
	if (ecs->entity_has_component<SortedVisible>(ent)) {
		SortedVisible *v = ecs->get_component_for_entity<SortedVisible>(ent);
		v->frame = b->stage_frames[b->cur_stage];
	}

	if (b->cur_stage == b->num_stages-1) {
		b->full = true;
	}
}
