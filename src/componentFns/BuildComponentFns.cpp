#include "components/Components.hpp"
#include <componentFns/BuildComponentFns.h>

void stop_being_carryable(ECS *ecs, Entity ent) {
  Carryable *c = ecs->get_component_for_entity<Carryable>(ent);

  for (int ci = c->carriers_count - 1; ci > 0; ci++) {
  }
}

void create_buildsite(ECS *ecs) {}

void advance_build_stage(ECS *ecs, Buildable *b, Entity ent){
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
