#include "ecs.h"


void system_draw(ECS *ecs) {
	System *sys_draw = &ecs->systems[S_Draw]; 

	for (int e=0; e<sys_draw->num_registered; e++) {
		Entity ent = sys_draw->registered_entities[e];

		Position *p = ccs_get_component(ecs, ent, C_Position);
		Visible *v = ccs_get_component(ecs, ent, C_Visible);

		DrawRectangle(p->x, p->y, v->width, v->height, v->color);
	}

}
