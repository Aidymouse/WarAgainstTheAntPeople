#include <systems/DamageSystem.h>
#include <engine/CollisionGrid.h>
#include <ecs/ECS.hpp>
#include <components/Components.hpp>
#include <util/Helper.h>
#include <util/ComponentFns.h>


/** Does general damage handling */
// Individual damage resopnses can be handled in respective systems because the colliders which provide damage will still be present (hopefully) by the time their updates roll around
// Literally the only damage case i handle does not do this you retard
void DamageSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
	for (std::set<Entity>::iterator e = registered_entities.begin(); e!=registered_entities.end(); e++) {
		Entity damageable_ent = (Entity) *e;

		Collider *col = ecs->get_component_for_entity<Collider>(damageable_ent);
		Damageable *dmg = ecs->get_component_for_entity<Damageable>(damageable_ent);

		std::set<Entity> damage_collisions = grid->get_collisions(*col, ecs);
		if (damage_collisions.size() == 0) continue;

		for (std::set<Entity>::iterator de = damage_collisions.begin(); de!=damage_collisions.end(); de++) {
			Entity damager_ent = (Entity)* de;
			if (damager_ent == damageable_ent) { continue; }
			if (!ecs->entity_has_component<Damager>(damager_ent)) { continue; }

			Damager *damage_data = ecs->get_component_for_entity<Damager>(damager_ent);

			if (!dmg->valid_damage_types[damage_data->damage_type]) { continue; }

			dmg->hp -= damage_data->damage;
			damage_data->damaged_this_frame = true;

			//std::cout << "[" << damageable_ent << "] taking damage" << std::endl;
			

		}
	}
}

void DamageSystem::process_post_damage_behaviours(ECS *ecs, CollisionGrid *grid) {
	std::shared_ptr<ComponentArray<Damager>> comp_damagers = ecs->get_component_array<Damager>();

	for (int e=0; e<comp_damagers->get_num_components(); e++) {
		Entity ent = comp_damagers->get_entity_from_idx(e);
		Damager d = comp_damagers->get_data_from_idx(e);

		if (!d.damaged_this_frame) return;
		
		// Follow post damage behaviour
		switch (d.post_damage_behaviour) {
			case (PostDamageBehaviours::PDB_DESTROY): {
				ComponentFns::clean_remove(ent, ecs, grid);
				e--;
				break;
			}
			case (PostDamageBehaviours::PDB_NOTHING): { break; }
		}
		

	}
}
