
#ifndef _SYSTEMS_H_
#define _SYSTEMS_H_

/** Define Systems Here **/
#define CCS_SYSTEMS \
	System(Move, CB_Position | CB_Velocity) \
	System(Draw, CB_Visible ) \

typedef struct ECS ECS; // My jank. Forware declare ECS so I can use it in system defs

void system_draw(ECS *ecs);

#endif
