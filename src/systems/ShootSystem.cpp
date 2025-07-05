#include <systems/ShootSystem.h>
#include <data/TextureStore.hpp>
#include <anim/NotMovingAnim.hpp>

void ShootSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {

	//std::cout << "Shoot System Updating" << std::endl;
  TextureStore &texture_store = TextureStore::getInstance();

	for (auto e = registered_entities.begin(); e!=registered_entities.end(); e++) {
		Entity shooter_id = (Entity)*e;
			std::cout << "[" << shooter_id <<"] shoot system" << std::endl;

		Shooter *s = ecs->get_component_for_entity<Shooter>(shooter_id);

		s->shoot_timer -= dt;
		if (s->shoot_timer <= 0) {
			std::cout << "[" << shooter_id <<"] shooting projectile" << std::endl;
			s->shoot_timer = s->shoot_interval;
			
			// Make projectile
			Position *p = ecs->get_component_for_entity<Position>(shooter_id);
			Vec2 target_pos = s->target_pos;

			Vec2 target_dir = (target_pos - Vec2(p->x, p->y)).normalized();

			Entity projectile_id = ecs->add_entity();
			ecs->add_component_to_entity<Visible>(projectile_id, {
				texture_store.get("rock"),
				NotMovingAnim.ROCK,
				-1,
				{0, 0}
			});
			ecs->add_component_to_entity<Position>(projectile_id, {
				p->x,
				p->y,
				0, // TODO this should probably be like 10 or something
			});
			ecs->add_component_to_entity<Transform>(projectile_id, {
				target_dir.x * 200,
				target_dir.y * 200,
				0, 
			});
		}
	}
};
