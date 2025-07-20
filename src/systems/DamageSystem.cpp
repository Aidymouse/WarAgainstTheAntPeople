#include <systems/DamageSystem.h>
#include <engine/CollisionGrid.h>
#include <ecs/ECS.hpp>
#include <components/Components.hpp>
#include <util/Helper.h>
#include <util/ComponentFns.h>


/** Does general damage handling */
// Individual damage resopnses can be handled in respective systems because the colliders which provide damage will still be present (hopefully) by the time their updates roll around
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
			
			// Follow post damage behaviour
			switch (damage_data->post_damage_behaviour) {
				case (PostDamageBehaviours::PDB_DESTROY): {
					ComponentFns::clean_remove(damager_ent, ecs, grid);
					break;
				}
				case (PostDamageBehaviours::PDB_NOTHING): { break; }
			}

		}
	}
}
