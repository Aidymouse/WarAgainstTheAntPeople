#include "components/Components.hpp"
#include <components/HivemindComponents.hpp>
#include "engine/CollisionGrid.h"
#include <data/TextureStore.hpp>
#include <data/AnimStore.hpp>
#include <state_machines/GuySM.h>
#include <data/Attrs.hpp>

#include <components/GuyComponents.hpp>

TextureStore &guy_sm_texture_store = TextureStore::getInstance();

g_Wandering *GuySM::start_wandering(Entity guy_id, ECS *ecs) {

	ecs->remove_component_from_entity<ScanningFor>(guy_id);

  int angle = rand() % 360;
  int speed = 20 + rand() % 30; // 20 - 50
  Vec2 dir = Vec2(1, 0);
  dir.face_angle(angle);
  float timer = (2 + rand() % 10) / 2.f;

  g_Wandering w = {timer, speed, dir};

  ecs->add_component_to_entity<g_Wandering>(guy_id, w);

  GuyBrain *g_Brain = ecs->get_component_for_entity<GuyBrain>(guy_id);
  //g_Brain->cur_state = GuyState::WANDERING;

  return ecs->get_component_for_entity<g_Wandering>(guy_id);
}

void GuySM::die(Entity guy_id, ECS *ecs, CollisionGrid *grid) {
	
	AnimStore &anim_store = AnimStore::getInstance();

	//std::cout << "[" << guy_id << "] is dying" << std::endl;
	Visible *vis = ecs->get_component_for_entity<Visible>(guy_id);

	vis->frame = anim_store.get("guy_squish0");
	vis->anim_timer = 0;

	GuyBrain *brain = ecs->get_component_for_entity<GuyBrain>(guy_id);
	// ecs->remove_component_from_entity<ScanningFor>(guy_id);
	ecs->remove_component_from_entity<Transform>(guy_id);
	ecs->remove_component_from_entity<g_Wandering>(guy_id);
	ecs->remove_component_from_entity<GuyBrain>(guy_id);
	ecs->remove_component_from_entity<Damageable>(guy_id);
	ecs->remove_component_from_entity<hv_Participant>(guy_id);

	// Stop carrying
	if (ecs->entity_has_component<Carrying>(guy_id)) {
		Entity carried_id = ecs->get_component_for_entity<Carrying>(guy_id)->carried_entity;
		Carryable *carryable = ecs->get_component_for_entity<Carryable>(carried_id);
		carryable->carriers_count -= 1;
		carryable->carrier_effort -= GuyAttrs.carry_strength;
	}

	ecs->remove_component_from_entity<Collider>(guy_id);
	grid->remove_entity(guy_id);

	//ecs->remove_component_from_entity<Collided>(guy_id);
}

/** Strips all guy brain related components */
void GuySM::stop_being_guy(Entity guy_id, ECS *ecs) {
	ecs->remove_component_from_entity<GuyBrain>(guy_id);
	ecs->remove_component_from_entity<g_Wandering>(guy_id);
}

// Guy has finished wandering, enter scanning (just for a frame)
void GuySM::end_wander_step(Entity guy_id, ECS *ecs) {
	ecs->remove_component_from_entity<g_Wandering>(guy_id);

	if (ecs->entity_has_component<hv_Brain>(guy_id)) {
		ecs->add_component_to_entity<ScanningFor>(guy_id, {
			{SCAN_VALUES::SV_BUILDSITE_WANT_SCRAP, SCAN_VALUES::SV_CARRIED_SCRAP, SCAN_VALUES::SV_SCRAP_METAL, SCAN_VALUES::SV_CARRIED_SCRAP_FULL},
			{GuyAttrs.scan_range, GuyAttrs.scan_range, GuyAttrs.scan_range, GuyAttrs.scan_range}
		});

	} else {
		ecs->add_component_to_entity<ScanningFor>(guy_id, {
			{SCAN_VALUES::SV_BUILDSITE_WANT_BUILDERS, SCAN_VALUES::SV_CARRIED_SCRAP, SCAN_VALUES::SV_SCRAP_METAL, -1},
			{GuyAttrs.scan_range, GuyAttrs.scan_range, GuyAttrs.scan_range, 0}
		});
	}


}
