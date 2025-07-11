#include "anim/BuildsiteAnim.hpp"
#include "components/Components.hpp"
#include <anim/BuildsiteAnim.hpp>
#include <systems/BuildSystem.h>
#include <componentFns/HivemindComponentFns.h>
#include <components/HivemindComponents.hpp>
#include <data/TextureStore.hpp>
#include <componentFns/BuildComponentFns.h>

void BuildSystem_check_resources(float dt, ECS *ecs, CollisionGrid *grid);
void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid);

/** Looks at build sites and resources and determines if a buildsite should be created or added to */
void BuildSystem::update(float dt, ECS *ecs, CollisionGrid *grid) {
  BuildSystem_check_resources(dt, ecs, grid);
  BuildSystem_check_buildsites(dt, ecs, grid);
}

void BuildSystem_check_resources(float dt, ECS *ecs, CollisionGrid *grid) {

	TextureStore &b_texture_store = TextureStore::getInstance();

  std::shared_ptr<ComponentArray<Resource>> comp_resource =
      ecs->get_component_array<Resource>();

  for (int r = 0; r < comp_resource->get_num_components(); r++) {
    Entity resource_id = comp_resource->get_entity_from_idx(r);

    //std::cout << "Checking build system for [" << resource_id << "]" << std::endl;
    // If two resources are touching and at least one of them is being carried
    // then they should transform into a buildsite
    Collider *resource_c = ecs->get_component_for_entity<Collider>(resource_id);

    bool is_carried = false;
    if (ecs->entity_has_component<Carryable>(resource_id)) {
      Carryable *resource_e =
          ecs->get_component_for_entity<Carryable>(resource_id);

      if (resource_e->carriers_count > 0) {
        is_carried = true;
      }
    }

    std::set<Entity> collided_resources = grid->get_collisions(*resource_c, ecs);

    for (auto resource_e = collided_resources.begin(); resource_e != collided_resources.end(); resource_e++) {
      Entity collided_resource_ent = (Entity)*resource_e;
      if (!ecs->entity_has_component<Resource>(collided_resource_ent)) { continue; }

      if (collided_resource_ent == resource_id) { continue; }

      if ((ecs->entity_has_component<Carryable>(collided_resource_ent) &&
           ecs->get_component_for_entity<Carryable>(collided_resource_ent) ->carriers_count > 0) ||
          is_carried) {
		// Remove whatever i collided with
		// Whatever was carrying this will get sorted out in the carry system
		// Need to update all the same stuff as the resource we collided with too though!!!
		
		//std::cout << "Removing [" << collided_resource_ent << "]" << std::endl;
		//ecs->debug_cout_entity_state(collided_resource_ent);
		
		if (ecs->entity_has_component<hv_Brain>(collided_resource_ent)) {
			// Resource is being carried most likely
			hv_Brain *hv = ecs->get_component_for_entity<hv_Brain>(collided_resource_ent);

			for (int e = 0; e<hv->num_entities; e++){
				ecs->add_component_to_entity<ScanningFor>(hv->entities[e], {{SCAN_VALUES::SV_CARRIED_SCRAP, SCAN_VALUES::SV_SCRAP_METAL, -1, -1}, {500, 500, 0, 0}});
				ecs->add_component_to_entity<HandsFree>(hv->entities[e], {});
			}

			dissolve_hivemind(ecs, collided_resource_ent);
			
		}
		grid->remove_entity(collided_resource_ent);
        ecs->remove_entity(collided_resource_ent);

        // Turn me into buildsite 
        // Tower for now cos i only have one
        ecs->remove_component_from_entity<Resource>(resource_id);

        ecs->remove_component_from_entity<Carryable>(resource_id);
		if (ecs->entity_has_component<Position>(resource_id)) {
			Position *p = ecs->get_component_for_entity<Position>(resource_id);
			p->z = 0;
		}

        ecs->remove_component_from_entity<ScanningFor>(resource_id);
        ecs->remove_component_from_entity<ScanningFor>(resource_id);
        ecs->remove_component_from_entity<Persuing>(resource_id);
        ecs->remove_component_from_entity<Transform>(resource_id);

        Buildable b = {
			0,
			4,
			{ bs_TowerAnim.BUILD1, bs_TowerAnim.BUILD2, bs_TowerAnim.BUILD3, bs_TowerAnim.BUILD4, },
			{0, 1, 1, 0},
			0,
			ResourceTypes::RT_SCRAP_METAL,
			StructureType::ST_TOWER,
			false
		};

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

        	ecs->add_component_to_entity<Buildable>(resource_id, b);
	
		Scannable *s = ecs->get_component_for_entity<Scannable>(resource_id);
		s->scan_value = SCAN_VALUES::SV_BUILDSITE_WANT_SCRAP;

		if (ecs->entity_has_component<hv_Brain>(resource_id)) {
			// Resource is being carried most likely
			hv_Brain *hv = ecs->get_component_for_entity<hv_Brain>(resource_id);

			for (int e = 0; e<hv->num_entities; e++){
				ecs->add_component_to_entity<ScanningFor>(hv->entities[e], {{SCAN_VALUES::SV_CARRIED_SCRAP, SCAN_VALUES::SV_SCRAP_METAL, -1, -1}, {500, 500, 0, 0}});
				ecs->add_component_to_entity<HandsFree>(hv->entities[e], {});
			}

			dissolve_hivemind(ecs, resource_id);
			
		}

      }
    }
  }
}

void BuildSystem_add_resource_to_buildsite(ECS *ecs, Entity buildsite_id, Entity resource_id) {
}

void BuildSystem_check_buildsites(float dt, ECS *ecs, CollisionGrid *grid) {

	std::shared_ptr<ComponentArray<Buildable>> comp_buildable = ecs->get_component_array<Buildable>();

	for (int e = 0; e<comp_buildable->get_num_components(); e++) {
		Entity buildsite_id = comp_buildable->get_entity_from_idx(e);
		Collider buildsite_collider = *(ecs->get_component_for_entity<Collider>(buildsite_id));
		std::set<Entity> col_ents = grid->get_collisions(buildsite_collider, ecs);
		Buildable *buildsite_buildable = ecs->get_component_for_entity<Buildable>(buildsite_id);
		if (buildsite_buildable->full) continue;

		for (auto ce=col_ents.begin(); ce!=col_ents.end(); ce++) {
			Entity collided_ent = (Entity) *ce;
			if (ecs->entity_has_component<Resource>(collided_ent)) { 
				Resource *collided_resource = ecs->get_component_for_entity<Resource>(collided_ent);
				if (collided_resource->type == buildsite_buildable->desired_resource) {
					
					// Add resource to buildsite
					buildsite_buildable->cur_build_points += collided_resource->value;
					
					// Clean Resource
					if (ecs->entity_has_component<hv_Brain>(collided_ent)) {
						hv_Brain *hv = ecs->get_component_for_entity<hv_Brain>(collided_ent);

						for (int e = 0; e<hv->num_entities; e++){
							ecs->add_component_to_entity<ScanningFor>(hv->entities[e], {{SCAN_VALUES::SV_SCRAP_METAL, -1, -1, -1}, {500, 0, 0, 0}});
							ecs->add_component_to_entity<HandsFree>(hv->entities[e], {});
						}
						dissolve_hivemind(ecs, collided_ent);
					}
					grid->remove_entity(collided_ent);
					ecs->remove_entity(collided_ent);

					// Progress Buildsite
					if (buildsite_buildable->cur_build_points >= buildsite_buildable->points_required[buildsite_buildable->cur_stage]) {
						advance_build_stage(ecs, buildsite_buildable, buildsite_id);

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

}


// TODO destruction subroutine
