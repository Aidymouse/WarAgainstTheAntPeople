#include <systems/DamageSystem.h>
#include <engine/CollisionGrid.h>
#include <ecs/ECS.hpp>
#include <components/Components.hpp>


void DamageSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
	for (std::set<Entity>::iterator e = registered_entities.begin(); e!=registered_entities.end(); e++) {
		Entity damageable_ent = (Entity) *e;

		Collider *col = ecs->get_component_for_entity<Collider>(damageable_ent);
		Damageable *dmg = ecs->get_component_for_entity<Damageable>(damageable_ent);

		/**
 		//TODO this is crashing oops;
		std::set<Entity> damage_collisions = grid->get_collisions(*col, ecs);
		for (std::set<Entity>::iterator de = damage_collisions.begin(); e!=damage_collisions.end(); de++) {
			Entity damager_ent = (Entity)* de;
			if (damager_ent == damageable_ent) { continue; }
			if (!ecs->entity_has_component<Damager>(damager_ent)) { continue; }
		}
		*/
	}
}
