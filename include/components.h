#include "raylib.h"

#define CCS_COMPONENTS \
	Component(Position, 1) \
	Component(Velocity, 2) \
	Component(Visible, 3) \

typedef struct Position {
	float x; 
	float y;
} Position;

typedef struct Velocity {
	float x_speed; 
	float y_speed;
} Velocity;

typedef struct Visible {
	int width;
	int height;
	Color color;
} Visible;

