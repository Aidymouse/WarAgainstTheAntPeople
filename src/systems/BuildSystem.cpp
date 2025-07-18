#include <data/Attrs.hpp>
#include <state_machines/GuySM.h>
#include <anim/BuildsiteAnim.hpp>
#include <components/Components.hpp>
#include <anim/BuildsiteAnim.hpp>
#include <systems/BuildSystem.h>
#include <components/HivemindComponents.hpp>
#include <data/TextureStore.hpp>
#include <util/ComponentFns.h>

void BuildSystem_check_resources(float dt, ECS *ecs, CollisionGrid *grid);
void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid);

/** Looks at build sites and resources and determines if a buildsite should be created or added to */
void BuildSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
  BuildSystem_check_resources(dt, ecs, grid);
  BuildSystem_check_buildsites(dt, ecs, grid);
}

bool is_carried(Entity ent, ECS *ecs) {
	return (ecs->entity_has_component<Carryable>(ent) && ecs->get_component_for_entity<Carryable>(ent)->carriers_count > 0);
}

/** Strips away all the resource related stuff from an entity, handling guy state 
 * Note only has the functionality common for both collided resources. One will then be removed and one will turn into a buildsite
 * */
void handle_resource_collision(Entity resource_id, ECS *ecs) {
	if (ecs->entity_has_component<hv_Brain>(resource_id)) {
		// If the resource is a hivemind then it's being carried 
		hv_Brain *hv = ecs->get_component_for_entity<hv_Brain>(resource_id);

		for (int e = 0; e<hv->num_entities; e++) {
			ecs->add_component_to_entity<ScanningFor>(hv->entities[e], {
				{SCAN_VALUES::SV_CARRIED_SCRAP, SCAN_VALUES::SV_SCRAP_METAL, -1, -1}, 
				{GuyAttrs.scan_range, GuyAttrs.scan_range, 0, 0}
			});

			ecs->add_component_to_entity<HandsFree>(hv->entities[e], {});
		}

		ComponentFns::remove_hivemind(resource_id, ecs);
	
	}
}

void BuildSystem_check_resources(float dt, ECS *ecs, CollisionGrid *grid) {

	TextureStore &b_texture_store = TextureStore::getInstance();

	std::shared_ptr<ComponentArray<Resource>> comp_resource = ecs->get_component_array<Resource>();

	for (int r = 0; r < comp_resource->get_num_components(); r++) {
		Entity resource_id = comp_resource->get_entity_from_idx(r);

		//std::cout << "Checking build system for [" << resource_id << "]" << std::endl;
		// If two resources are touching and at least one of them is being carried then they should transform into a buildsite
		Collider *resource_c = ecs->get_component_for_entity<Collider>(resource_id);

		std::set<Entity> collided_resources = grid->get_collisions(*resource_c, ecs);

		for (auto col_res_e = collided_resources.begin(); col_res_e != collided_resources.end(); col_res_e++) {
			Entity collided_id = (Entity)*col_res_e;
			if (!ecs->entity_has_component<Resource>(collided_id)) { continue; }

			if (collided_id == resource_id) { continue; }
			
			// We have collided with another resource!
			// I'm going to turn into a buildsite, whatever I collided with is going to be removed

			handle_resource_collision(collided_id, ecs);
			if (ecs->entity_has_component<Carryable>(collided_id) && ecs->get_component_for_entity<Carryable>(collided_id)->carriers_count > 0) {
				std::cout << "[" << resource_id << "] collided with also carried resource [" << collided_id << "]" << std::endl;
			}
			ComponentFns::clean_remove(collided_id, ecs, grid);

			// Turn me into buildsite 
			// Tower for now cos i only have one
			handle_resource_collision(resource_id, ecs);

			ecs->remove_component_from_entity<Resource>(resource_id);

			ecs->remove_component_from_entity<Carryable>(resource_id);
			if (ecs->entity_has_component<Position>(resource_id)) {
				Position *p = ecs->get_component_for_entity<Position>(resource_id);
				p->z = 0;
			}

			GuySM::stop_being_guy(resource_id, ecs);

			ecs->remove_component_from_entity<ScanningFor>(resource_id);
			ecs->remove_component_from_entity<Persuing>(resource_id);
			ecs->remove_component_from_entity<Transform>(resource_id);

			Buildable b = {
				0,
				4,
				{bs_TowerAnim.BUILD1, bs_TowerAnim.BUILD2, bs_TowerAnim.BUILD3, bs_TowerAnim.BUILD4},
				{0, 1, 1, 0},
				0,
				ResourceTypes::RT_SCRAP_METAL,
				StructureType::ST_TOWER,
				false
			};

			ecs->add_component_to_entity<Buildable>(resource_id, b);

			Visible *v = ecs->get_component_for_entity<Visible>(resource_id);
			v->texture = b_texture_store.get("tower");
			v->frame = b.stage_frames[0];

			SortedVisible sv;
			sv.texture = v->texture;
			sv.frame = b.stage_frames[0];
			sv.anim_timer = b.stage_frames[0].duration;
			sv.offset.x = v->offset.x;
			sv.offset.y = v->offset.y;

			ecs->add_component_to_entity<SortedVisible>(resource_id, sv);
			ecs->remove_component_from_entity<Visible>(resource_id);
			
			Scannable *s = ecs->get_component_for_entity<Scannable>(resource_id);
			s->scan_value = SCAN_VALUES::SV_BUILDSITE_WANT_SCRAP;

		}
	}
}

void BuildSystem_add_resource_to_buildsite(ECS *ecs, Entity buildsite_id, Entity resource_id) {
}


void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid) {

	std::shared_ptr<ComponentArray<Buildable>> comp_buildable = ecs->get_component_array<Buildable>();

	for (int e = 0; e<comp_buildable->get_num_components(); e++) {
		Entity buildsite_id = comp_buildable->get_entity_from_idx(e);
		Collider buildsite_collider = *ecs->get_component_for_entity<Collider>(buildsite_id);
		std::set<Entity> col_ents = grid->get_collisions(buildsite_collider, ecs);
		Buildable *buildsite_buildable = ecs->get_component_for_entity<Buildable>(buildsite_id);
		if (buildsite_buildable->full) continue;

		for (auto ce=col_ents.begin(); ce!=col_ents.end(); ce++) {
			Entity collided_ent = (Entity) *ce;
		
			if (ecs->entity_has_component<Resource>(collided_ent)) { 
				Resource *collided_resource = ecs->get_component_for_entity<Resource>(collided_ent);
				if (!collided_resource->type == buildsite_buildable->desired_resource) { return; } 
					
				// Add resource to buildsite
				buildsite_buildable->cur_build_points += collided_resource->value;
				
				// Clean Resource
				handle_resource_collision(collided_ent, ecs);
				ComponentFns::clean_remove(collided_ent, ecs, grid);

				// Progress Buildsite
				if (buildsite_buildable->cur_build_points >= buildsite_buildable->points_required[buildsite_buildable->cur_stage]) {
					ComponentFns::advance_build_stage(ecs, buildsite_buildable, buildsite_id);

					// TODO turn fully built site into designated structure					
					if (buildsite_buildable->full) {
						ecs->remove_component_from_entity<Scannable>(buildsite_id);	
						Shooter s = {
							ProjectileType::PT_ROCK,
							10,
							2,
							Vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2)
						};
						ecs->add_component_to_entity<Shooter>(buildsite_id, s);	
					}
				}
					
					
				
			}
		}
	}

}


// TODO destruction subroutine
