#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <bitset>
#include <engine/Collisions.h>
#include <ecs/Entity.hpp>

enum COMP_SIG { // Component Signature Indexes
	POSITION = 0,
	VISIBLE = 1,
	TOOL = 2,
	CLICKABLE = 3,
	COLLIDER = 4,
	COL_MALLET = 5,

	SCANNING_FOR = 6,
	SCANNABLE = 7,
	PERSUING = 8,
};

struct Position {
	float x;
	float y;
};

struct Tool {
	int collision_idx;
};

/*struct Carrier { */
/*	Entity carried_ent;*/
/*};*/
/**/
/*struct Carried {*/
/*	Entity guy_carrying = -1; // If it's -1 it's on the ground*/
/*};*/

/*struct MachineBeingBuilt {*/
/*	int progress = 0;*/
/*};*/

enum SCAN_VALUES {
	SCRAP = 0,
};

struct ScanningFor {
	int sought_scan_value;
};

struct Scannable {
	int scan_value;
};

struct Persuing {
	float desiredX;
	float desiredY;
};

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





