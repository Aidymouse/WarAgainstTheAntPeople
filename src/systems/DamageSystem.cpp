#include <systems/DamageSystem.h>
#include <engine/CollisionGrid.h>
#include <ecs/ECS.hpp>
#include <components/Components.hpp>
#include <util/Helper.h>


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
			
			grid->remove_entity(damager_ent);
			ecs->remove_entity(damager_ent);
			//Collider damager_collider = ecs->get_component_for_entity<Collider>(damager_ent);
		}
	}
}
