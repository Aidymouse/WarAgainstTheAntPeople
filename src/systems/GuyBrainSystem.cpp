// System that handles making decisions for a guy. The only thing we know for
// sure is that we have a guy present. This is, like, probably against ECS ethos
// or some shit.
//
#include "components/Collisions.hpp"
#include "components/Components.hpp"
#include "components/HivemindComponents.hpp"
#include "state_machines/GuySM.h"
#include "util/Random.h"
#include <ProjectConfig.h>
#include <components/GuyComponents.hpp>
#include <ecs/ECS.hpp>
#include <systems/GuyBrainSystem.h>
#include <cmath>

#include <anim/GuyAnim.hpp>
#include <data/TextureStore.hpp>
#include <engine/CollisionGrid.h>

void gs_wander(float dt, ECS *ecs);
void g_handle_collisions(float dt, ECS *ecs);

const bool guy_brain_debug = false;

TextureStore &gbs_ts = TextureStore::getInstance();

void GuyBrainSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
  // /** Decision Making - aka switch between states */
	for (auto e = registered_entities.begin(); e != registered_entities.end(); e++) {
  
		Entity guy_id = (Entity)*e;
  
  
		Signature skip_guy_processing;
		skip_guy_processing[COMP_SIG::HV_PARTICIPANT] = 1;
		//skip_guy_processing[COMP_SIG::HV_BRAIN] = 1;
		if ((ecs->get_signature_for_entity(guy_id) & skip_guy_processing) != 0) {
			continue;
		}
		  
		// TODO: todays mystery, why do the guys stop moving after they've done one build?
		// They *are* continuing to scan, maybe their carrier isn't removed?
		/** Check if guy is preoccupied */
		bool preoccupied = false;
		Signature s = (2 << (int)COMP_SIG::PERSUING-1) + (2 << (int)COMP_SIG::CARRIER-1);

		if (ecs->entity_has_any_components(guy_id, s)) {
			preoccupied = true;
			//ecs->debug_cout_entity_state(guy_id);
			/*
			std::cout << "Entity [" << guy_id << "] " << ecs->get_signature_for_entity(guy_id) << std::endl;
			std::cout << "Entity [" << guy_id << "] " << s << std::endl;
			std::cout << std::endl;
			*/
		} 

		if (preoccupied) continue;

		//std::cout << "Processing guy up top decision making for [" << guy_id << "]" << std::endl;

		// Decision making code goes here, one day
		if (!ecs->entity_has_component<g_Wandering>(guy_id)) { GuySM::enter_wandering(guy_id, ecs); }
		

		//if (!ecs->entity_has_any_components(guy_id, s)) {
		//std::cout << s << std::endl;
		/*
		if (!ecs->entity_has_component<Persuing>(guy_id) && !ecs->entity_has_component<g_Wandering>(guy_id)) {
		}
*/
  
     /** DEBUG */
   }

  // Sub system calls
  // g_handle_collisions(dt, ecs, grid);
  gs_wander(dt, ecs);
}

void GuyBrainSystem::g_handle_collisions(float dt, ECS *ecs, CollisionGrid *grid) {
	for (auto e = registered_entities.begin(); e != registered_entities.end(); e++) {

		Entity guy_id = (Entity)*e;

		if (!ecs->entity_has_component<Collided>(guy_id))
			continue;

		if (guy_brain_debug) {
			std::cout << "Guy (" << guy_id << ") has collisions" << std::endl;
		}

		Collided *co = ecs->get_component_for_entity<Collided>(guy_id);

		for (int c = 0; c < co->num_collisions; c++) {
			bool cancel_remaining_collision_checks = false;
			Collision col = co->collisions[c];
			// Switch through collisions
			switch (col.type) {

			case CollisionType::IDENTIFIER: {
				if (col.data.identifier.id == Identifier::SCRAP_METAL) {
				// Transform into PICK_ME_UP
				co->collisions[c].type = CollisionType::PICK_ME_UP;
				co->collisions[c].data.pick_me_up = {
					co->collisions[c].data.identifier.entity_id};
				}

				c--;

				break;
			}

			case CollisionType::SQUISH: {
				GuySM::die(guy_id, ecs, grid);
				// return; // Don't handle any more collisions after a guy has died!
				cancel_remaining_collision_checks = true;
				break;
			}

			case CollisionType::GO_SOMEWHERE_ELSE: {
				if (co->num_collisions > 1)
					break;
				g_Wandering *w = GuySM::enter_wandering(guy_id, ecs);
				Position *p = ecs->get_component_for_entity<Position>(guy_id);

				Vec2 pos_away_from = Vec2(col.data.go_somewhere_else.pos_away_from_x,
																	col.data.go_somewhere_else.pos_away_from_y);

				Vec2 away_from = Vec2(p->x, p->y) - pos_away_from;
				float angle_away = away_from.get_angle_facing();
				int new_angle = Random::rand_range(angle_away - 60, angle_away + 60);

				Vec2 dir = Vec2(1, 0);
				dir.face_angle(new_angle);
				w->dir = dir;
				break;
			}
			default: {
				break;
			}
	}

			if (cancel_remaining_collision_checks)
				break;
		}
	}
}

/** The guy wanders around aimlessly until they get in range of something cooler
 * Thusly, they should probably be looking around as well...
 */
void gs_wander(float dt, ECS *ecs) {
	/** Wandering */
	std::shared_ptr<ComponentArray<g_Wandering>> comp_wandering = ecs->get_component_array<g_Wandering>();

	for (int i = 0; i < comp_wandering->get_num_components(); i++) {
		Entity e = comp_wandering->get_entity_from_idx(i);

		g_Wandering *wander_data = comp_wandering->get_editable_data(e);
		Transform *t = ecs->get_component_for_entity<Transform>(e);
		Position *p = ecs->get_component_for_entity<Position>(e);

		wander_data->timer -= dt;
		t->vel_x = wander_data->dir.x * wander_data->speed;
		t->vel_y = wander_data->dir.y * wander_data->speed;

		if (wander_data->timer < 0) {
			int angle = Random::rand_range(0, 360);
			int speed = Random::rand_range(20, 50);
			Vec2 dir = Vec2(1, 0);
			dir.face_angle(angle);
			float timer = Random::rand_range(2, 6) / 2.f;

			wander_data->dir = dir;
			wander_data->speed = speed;
			wander_data->timer = timer;
		}

		// Make guy decide to turn around if they're about to walk off the edge
		int angle_min = 0;
		int angle_max = 0;
		if (p->y < 5 && wander_data->dir.y < 0) {
			angle_min = 90;
			angle_max = 270;
		} else if (p->y > WINDOW_HEIGHT - 5 && wander_data->dir.y > 0) {
			angle_min = -90;
			angle_max = 90;
		}
		if (p->x < 5 && wander_data->dir.x < 0) {
			angle_min = 0;
			angle_max = 180;
		} else if (p->x > WINDOW_WIDTH - 5 && wander_data->dir.x > 0) {
			angle_min = 180;
			angle_max = 360;
		}
		if (angle_min + angle_max != 0) {
			int angle = Random::rand_range(angle_min, angle_max);
			Vec2 dir = Vec2(0, -1);
			dir.face_angle(angle);
			wander_data->dir = dir;
		}
	}
}
