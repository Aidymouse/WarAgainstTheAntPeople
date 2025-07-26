#include <data/Attrs.hpp>
#include <engine/CollisionGrid.h>
#include <components/Components.hpp>
#include <components/GuyComponents.hpp>
#include <components/HivemindComponents.hpp>
#include <systems/CarrySystem.h>
#include <util/ComponentFns.h>

void process_pickup(float dt, std::set<Entity> *registered_entities, ECS *ecs,
										CollisionGrid *grid);
void strip_invalid_carrieds(ECS *ecs);
void process_drop(float dt, ECS *ecs);

void CarrySystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
	strip_invalid_carrieds(ecs);
	process_drop(dt, ecs);

	process_pickup(dt, &registered_entities, ecs, grid);

}

/** It's possible that the thing a guy is carrying has been destroyed 
 * We only have a carrier->carried relationship so we check here to strip them out */
void strip_invalid_carrieds(ECS *ecs) {
	std::shared_ptr<ComponentArray<Carrying>> comp_carriers = ecs->get_component_array<Carrying>();
	for (int c = 0; c < comp_carriers->get_num_components(); c++) {
		// Entity c_ent = comp_carriers->get_entity_from_idx(c);
		Carrying *ca = comp_carriers->get_editable_data_from_idx(c);

		Entity carried_ent = ca->carried_entity;
		if (!ecs->entity_has_component<Carryable>(carried_ent)) {
			Entity carrying_ent = comp_carriers->get_entity_from_idx(c);
			ecs->remove_component_from_entity<Carrying>(carrying_ent);
			// TODO: handsfree?
		}
	}
}


/** If I have nothing left carrying me, stop being carried */
void process_drop(float dt, ECS *ecs) {
	std::shared_ptr<ComponentArray<Carryable>> comp_carryables = ecs->get_component_array<Carryable>();
	for (int c = 0; c < comp_carryables->get_num_components(); c++) {
		Carryable carryable = comp_carryables->get_data_from_idx(c);
		
		if (carryable.carriers_count == 0) {
			Entity carryable_id = comp_carryables->get_entity_from_idx(c);
			if (ecs->entity_has_component<hv_Brain>(carryable_id)) {
				ComponentFns::remove_hivemind(carryable_id, ecs);
				ecs->remove_component_from_entity<Transform>(carryable_id); // TODO: should this be in remove hivemind???
			}

			Position *p = ecs->get_component_for_entity<Position>(carryable_id);
			p->z = 0;
		}
		
	}
	
}

/** When an item is picked up, it transforms into a guy itself and becomes a hivemind for all participating guys 
 * Yknow actually maybe being part of a hivemind should be processed on a guy by guy basis if we're currently carrying something, but whatever.
 * The carried resource has scan targets and pursues them in ScanningSystem
 * */
void process_pickup(float dt, std::set<Entity> *registered_entities, ECS *ecs, CollisionGrid *grid) {

	std::shared_ptr<ComponentArray<Carryable>> comp_carryable = ecs->get_component_array<Carryable>();

	for (auto carryable_e = registered_entities->begin(); carryable_e != registered_entities->end(); carryable_e++) {
		Entity carryable_ent = (Entity)*carryable_e;

		Collider *carryable_col = ecs->get_component_for_entity<Collider>(carryable_ent);

		std::set<Entity> collided = grid->get_collisions(*carryable_col, ecs);
		for (auto collided_e = collided.begin(); collided_e != collided.end(); collided_e++) {
			Entity picking_up_ent = (Entity)*collided_e;

			if (picking_up_ent == carryable_ent) continue;

			Signature s;
			s[COMP_SIG::HANDSFREE] = 1;
			s[COMP_SIG::GUY_BRAIN] = 1;
			// s[COMP_SIG::CARRIER] = 1;

			// TODO we should do the already in check OUT HERE!!!
			
			// If we're relying on hands being free we might as well not check it at all! You need hands free to even be registered here
			if (ecs->entity_has_components(picking_up_ent, s)) {

				Entity pickup_id = carryable_ent;
				Entity guy_id = picking_up_ent;

				// Set up the hivemind and carryable state
				if (!ecs->entity_has_component<hv_Brain>(pickup_id)) {
					hv_Brain newB;
					for (int i = 0; i < MAX_ENTITIES_IN_HIVEMIND; i++) {
						newB.entities[i] = -1;
					}
					newB.num_entities = 0;

					ecs->add_component_to_entity<hv_Brain>(pickup_id, newB);
					// b.num_entities = 1;
					// b.entities[0] = guy_id;

					// ScanningFor will be set up in guy brain system

					ecs->add_component_to_entity<Transform>(pickup_id, {0, 0, 0});
					ecs->add_component_to_entity<GuyBrain>(pickup_id, {GuyMood::GM_BUILDER, 0});
					// GuySM::enter_wandering(pickup_id, ecs);

					if (ecs->entity_has_component<Scannable>(pickup_id)) {
						Scannable *s = ecs->get_component_for_entity<Scannable>(pickup_id);
						s->scan_value = SCAN_VALUES::SV_CARRIED_SCRAP;
						//std::cout << "Set new scan value" << s->scan_value << std::endl;
					}

					// ecs->debug_cout_entity_state(pickup_id);
				}

				// Update hivemind and carrier status
				hv_Brain *b = ecs->get_component_for_entity<hv_Brain>(pickup_id);
				Carryable *c = ecs->get_component_for_entity<Carryable>(pickup_id);

				bool already_in = false;
				for (int in = 0; in < b->num_entities; in++) {
					if (b->entities[in] == guy_id) {
						already_in = true;
						break;
					}
				}

				if (!already_in && c->carriers_count < c->carrier_limit) {
					// Start carrying
					ecs->remove_component_from_entity<ScanningFor>(guy_id);
					ecs->remove_component_from_entity<Persuing>(guy_id);
					ecs->remove_component_from_entity<HandsFree>(guy_id);

					b->entities[b->num_entities] = guy_id;
					b->num_entities += 1;

					Position *guy_pos = ecs->get_component_for_entity<Position>(guy_id);

					Position *pickup_pos = ecs->get_component_for_entity<Position>(pickup_id);
					pickup_pos->z = 5;

					hv_Participant guy_hv;
					Vec2 off = Vec2(guy_pos->x, guy_pos->y) - Vec2(pickup_pos->x, pickup_pos->y);
					guy_hv.offset = off;

					ecs->add_component_to_entity<hv_Participant>(guy_id, guy_hv);

					ecs->add_component_to_entity<Carrying>(guy_id, {pickup_id});
					// .... we dont actually give the guy carrier. Oops */
					// TODO: use a guys Carrier component
					c->carriers_count += 1;
					c->carrier_effort += GuyAttrs.carry_strength;
					// std::cout << "Adding [" << guy_id << "] to carryable " << pickup_id << "(" << c->carriers_count << " / " << c->carrier_limit << ")" << std::endl;

					Transform *trans = ecs->get_component_for_entity<Transform>(guy_id);
					trans->vel_x = 0;
					trans->vel_y = 0;
					trans->vel_z = 0;

					if (c->carriers_count == c->carrier_limit) {
						Scannable *picked_up_scannable = ecs->get_component_for_entity<Scannable>(pickup_id);
						picked_up_scannable->scan_value = SCAN_VALUES::SV_CARRIED_SCRAP_FULL;
					}
				}
			}
		}
	}
}
