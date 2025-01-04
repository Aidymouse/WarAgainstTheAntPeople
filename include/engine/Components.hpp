#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <bitset>
#include <engine/Collisions.h>

enum COMP_SIG { // Component Signature Indexes
	POSITION = 0,
	VISIBLE = 1,
	TOOL = 2,
	CLICKABLE = 3,
	COLLIDER = 4,
	COL_MALLET = 5,
};

struct Position {
	float x;
	float y;
};

struct Tool {
	int collision_idx;
};

struct Guy { };

struct Collider {
	CollisionShapeType type;
	CollisionShape shape;
	std::bitset<4> collided_with; // Index of object collided with
	// 1: Mallet
};

struct ColliderHandler_mallet {
};

struct Visible {
	std::shared_ptr<sf::Sprite> sprite;
};


struct Clickable {};





