
#define ECS_IMPLEMENTATION

#include "ecs.h"

#undef ECS_IMPLEMENTATION

#include <stdio.h>
#include "raylib.h"
#include "helper.h"
#include <time.h>

#include "structs/state.h"

#include "defines/defaultOptions.h"
//#include <assert.h>

#define NUM_ANT_PEOPLE 100
#define NUM_ROCKS 100
	
void init_gamestate(GameState *state) {
	state->health = 100;
	state->num_rocks = 0;
}

int main() {

	GameState gamestate;
	init_gamestate(&gamestate);

	srand(time(NULL));

	ECS ecs;
	ccs_init_ecs(&ecs);

	float window_width = DEFAULT_WINDOW_WIDTH;
	float window_height = DEFAULT_WINDOW_HEIGHT;

	InitWindow(window_width, window_height, "War Against the Ant People");
	SetTargetFPS(60);


	// Set up ant people
	for (int i=0; i< NUM_ANT_PEOPLE; i++) {
		Entity e = ccs_add_entity(&ecs);
		if (!e) { continue; }

		Visible *v = ccs_add_component(&ecs, e, C_Visible);
		v->width = 16;
		v->height = 16;
		v->color = BLUE;

		Position *p = ccs_add_component(&ecs, e, C_Position);
		p->x = randInt(0, 800);
		p->y = randInt(0, 800);
	}

	for (int i=0; i< NUM_ROCKS; i++) {
		Entity e = ccs_add_entity(&ecs);
		if (!e) { continue; }

		Visible *v = ccs_add_component(&ecs, e, C_Visible);
		v->width = 8;
		v->height = 8;
		v->color = GRAY;

		Position *p = ccs_add_component(&ecs, e, C_Position);
		p->x = randInt(0, 800);
		p->y = randInt(0, 800);
	}

	Entity ed = 1;

	while (!WindowShouldClose()) {

		ClearBackground(BLACK);
		BeginDrawing();
	
		/** Draw System **/

		system_draw(&ecs);

		// Main Base
		DrawCircleLines(window_width/2, window_height/2, 50, BLUE);

		EndDrawing();
	}

	return 0;
}
