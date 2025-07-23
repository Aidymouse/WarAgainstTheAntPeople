#include <systems/ShootSystem.h>
#include <data/TextureStore.hpp>
#include <util/Spawners.h>
#include <data/AnimStore.hpp>

void update_projectiles(float dt, ECS *ecs, CollisionGrid *grid);

void ShootSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {

	update_shooters(dt, ecs, grid);
	//update_projectiles(dt, ecs, grid);

};

void ShootSystem::update_shooters(float dt, ECS *ecs, CollisionGrid *grid) {

	//std::cout << "Shoot System Updating" << std::endl;
  	//TextureStore &texture_store = TextureStore::getInstance();
	AnimStore &anim_store = AnimStore::getInstance();

	for (auto e = registered_entities.begin(); e!=registered_entities.end(); e++) {
		Entity shooter_id = (Entity)*e;
			//std::cout << "[" << shooter_id <<"] shoot system" << std::endl;

		Shooter *s = ecs->get_component_for_entity<Shooter>(shooter_id);

		s->shoot_timer -= dt;
		if (s->shoot_timer <= 0) {
			std::cout << "[" << shooter_id <<"] shooting projectile" << std::endl;
			s->shoot_timer = s->shoot_interval;
			
			// Make projectile
			Position *p = ecs->get_component_for_entity<Position>(shooter_id);
			Vec2 target_pos = s->target_pos;

			Vec2 target_dir = (target_pos - Vec2(p->x, p->y)).normalized();

			Spawners::shoot_rock(ecs, grid, Vec2(p->x, p->y), target_dir);
		}
	}

}

void update_projectiles(float dt, ECS *ecs, CollisionGrid *grid) {
}
