#include <componentFns/HivemindComponentFns.h>
#include <components/HivemindComponents.hpp>

void dissolve_hivemind(ECS *ecs, Entity ent) {
	
	hv_Brain *hv = ecs->get_component_for_entity<hv_Brain>(ent);

	for (int e=0; e<hv->num_entities; e++) {
		ecs->remove_component_from_entity<hv_Participant>(ent);
	}
	
	ecs->remove_component_from_entity<hv_Brain>(ent);
}
