#pragma once

#include <SDL3/SDL.h>
#include <bitset>
#include <components/Collisions.hpp>
#include <ecs/Entity.hpp>
#include <engine/Collisions.h>
#include <memory>
#include <optional>
#include <util/UtilTypes.hpp>
#include <data/AnimStore.hpp>


enum COMP_SIG { // Component Signature Indexes
	EXISTS = 0,

	POSITION = 1,

	VISIBLE = 2,
	DECORATION=3,
	SORTEDVISIBLE = 4,
	TRANSFORM = 5,

	FOLLOWS_MOUSE = 6,

	SCANNING_FOR = 7,
	SCANNABLE = 8,
	CARRYING = 9,
	CARRYABLE = 10,
	PERSUING = 11,

	COLLIDER = 12,
	COLLIDED = 13,

	BUILDABLE = 14,
	BUILDER = 15, 

	RESOURCE = 16,

	// GUY
	GUY_BRAIN = 17,
	GUY_WANDERING = 18,

	// Hivemind
	HV_BRAIN = 19,
	HV_PARTICIPANT = 20,

	// Traits
	HANDSFREE = 21,

	SHOOTER = 22,
	PROJECTILE = 23,

	DAMAGEABLE = 24,
	DAMAGER = 25,

	STAPLEDTO = 26, // Move my position to match

};

struct FollowsMouse {
  short speed; // Speed at which item pursues mouse. If -1 it will snap to the
               // mouse, no travel time
};


struct Position {
  float x;
  float y;
  float z;
};

struct ZEnabled {
  float z; // Used for fake 3d. Subtracted from Y to get vertical pos on screen,
           // but sorted with higher Z = higher. Z < 0 is ignored, so can be
           // used to order stuff on the ground.
};

struct Transform {
  float vel_x;
  float vel_y;
  float vel_z;
};

enum SCAN_VALUES {
  SV_SCRAP_METAL = 0,
  SV_BUILD_SITE = 1,

  SV_BUILDSITE_WANT_SCRAP = 3,
  SV_BUILDSITE_WANT_BUILDERS = 4,

  SV_CARRIED_SCRAP = 16,
  SV_CARRIED_SCRAP_FULL = 17,
  // CARRIED_SCRAP = 1,
};

#define MAX_SCAN_VALUES 4
struct ScanningFor {
  int sought_scan_values[MAX_SCAN_VALUES];
  float max_range[MAX_SCAN_VALUES];
};

struct Scannable {
  int scan_value;
};

struct Persuing {
  float desiredX;
  float desiredY;
};

struct Collided {
  Collision collisions[MAX_COLLISIONS_PER_ENTITY]; // You can collide with up to this many things per frame
  int num_collisions;
};

struct HandsFree {};

enum CollisionIdentifier {
	CI_HAND=0,
	CI_BASE=0,
	CI_RESOURCE=16,
	CI_GUY=17,
	CI_ROCK=18,
};

struct Collider {
	CollisionShapeType type;
	CollisionShape shape;
	CollisionIdentifier identifier;
};

/** Unused
#define MAX_MULTI_COLLISIONS 4
struct MultiCollider {
  CollisionShapeType types[MAX_MULTI_COLLISIONS];
  CollisionShape shapes[MAX_MULTI_COLLISIONS];
  Collision collidion_datas[MAX_MULTI_COLLISIONS];
};
*/


// Can be smashed by big weights (like hammer)
struct Smashable {};


struct StapledTo {
	Entity entity;
	xy offset; // Offset from entities position
};

// Same as visible except drawn seperately
struct SortedVisible {
  AnimFrame frame;
  float anim_timer;
  xy offset; // For texture shifting, in addition to frames offset
};

struct Visible {
  AnimFrame frame;
  float anim_timer;
  xy offset; // For texture shifting, in addition to frames offset

/* TODO some kind of auto conversion from sorted visible to visible.
	explicit Visible(const SortedVisible& s_vis) { 
	}
*/
};

// Same as Visible except drawn before the guys
struct Decoration {
  AnimFrame frame;
  float anim_timer;
  xy offset; // For texture shifting, in addition to frames offset
};


enum ResourceTypes { RT_SCRAP_METAL };

struct Resource {
  ResourceTypes type;
  short value;
};


enum StructureType { ST_TOWER };

#define MAX_BUILDABLE_STAGES 4
struct Buildable {
	int cur_stage;
	int num_stages;
	AnimFrame stage_frames[MAX_BUILDABLE_STAGES];

	short resource_points;
	short req_resource_points[MAX_BUILDABLE_STAGES];
	ResourceTypes desired_resource;
	bool full; // Can't have any more resource

	short req_build_points[MAX_BUILDABLE_STAGES];
	short build_points;
};

struct Builder { };

enum ProjectileType { PT_ROCK };
struct Shooter {
	ProjectileType projectile_type;
	float shoot_interval;
	float shoot_timer;
	Vec2 target_pos;
};

struct Projectile {
	int damage;
};

struct Carrying {
  Entity carried_entity;
  //int contributing_effort;
};

struct Carryable {
	int carriers_count; // How many guys carrying currently
	int carrier_effort; // total effort of carriers - higher number = move faster
	int carrier_limit;
	int weight; // Heavier things are harder to move
	int min_weight; // Minimum weight required to move at all
};

// Guy States
enum GuyState { 
	GS_LOOK_FOR_RESOURCES,
	GS_LOOK_TO_BUILD 
};

// Keeps the meta-information regarding a guys current state, for decision
// making purposes
struct GuyBrain {
  GuyState cur_state;
  float die_timer;
};


#define NUM_DAMAGE_TYPES 3
#define DamageSignature std::bitset<NUM_DAMAGE_TYPES>
struct Damageable {
	int hp;
	DamageSignature valid_damage_types;
};


enum DamageTypes {
	DT_LIGHTSQUISH=0,
	DT_HEAVYSQUISH=1, // Splat, hammer, etc
	DT_FIRE=2, 
};

enum PostDamageBehaviours {
	PDB_DESTROY=0, // Removes entity entirely on damage
	PDB_NOTHING=2, // As it says on the tin
};
struct Damager {
	int damage;
	DamageTypes damage_type;
	bool damaged_this_frame; // True if we did that
	PostDamageBehaviours post_damage_behaviour;
};
