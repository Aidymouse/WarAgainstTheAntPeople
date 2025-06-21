#pragma once

#include <SDL3/SDL.h>
#include <anim/Anim.hpp>
#include <bitset>
#include <components/Collisions.hpp>
#include <ecs/Entity.hpp>
#include <engine/Collisions.h>
#include <memory>
#include <optional>

enum COMP_SIG { // Component Signature Indexes
  RESERVED = 0,
  POSITION = 1,
  ZENABLED = 2,
  VISIBLE = 3,
  SORTEDVISIBLE = 4,
  TRANSFORM = 5,
  SCANNING_FOR = 6,
  SCANNABLE = 7,

  FOLLOWS_MOUSE = 8,

  // TOOL = 3,
  // CLICKABLE = 4,
  COLLIDER = 9,
  GUY_BRAIN = 10,

  GUY_WANDERING = 11,
  CARRIER = 12,
  CARRYABLE = 13,
  COLLIDED = 14,

  // COL_MALLET = 7,
  //
  // SCANNABLE = 8,
  // PERSUING = 9,
};

struct FollowsMouse {
  short speed; // Speed at which item pursues mouse. If -1 it will snap to the
               // mouse, no travel time
};

struct Reserved {
  Entity ent;
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
  SV_SCRAP_METAL = 0,
  SV_BUILD_SITE = 1,
  // CARRIED_SCRAP = 1,
};

struct ScanningFor {
  int sought_scan_value;
  float max_range;
};

struct Scannable {
  int scan_value;
};

struct Persuing {
  float desiredX;
  float desiredY;
};

// struct Collision {
//   Entity collided_entity;
// };

struct Collided {
  Collision collisions[4]; // You can collide with up to four things on a frame
};

struct Collider {
  CollisionShapeType type;
  CollisionShape shape;
  Collision collision_data;
};

// Can be smashed by big weights (like hammer)
struct Smashable {};

struct xy {
  int x;
  int y;
};

struct Visible {
  SDL_Texture *texture;
  AnimFrame frame;
  float anim_timer;
  xy offset; // For texture shifting
};

// Same as visible except drawn seperately
struct SortedVisible {
  SDL_Texture *texture;
  AnimFrame frame;
  float anim_timer;
  xy offset; // For texture shifting
};

struct Clickable {};

enum RESOURCE_TYPES { RT_SCRAP_METAL };

struct Collectable_Resource {
  RESOURCE_TYPES type;
  short value;
};

struct Buildable {
  unsigned short points_required;
  unsigned short cur_build_points;
};

struct Carrier {
  std::optional<Entity> carried_entity;
  int contributing_effort;
};

struct Carryable {
  int carriers_count; // How many guys carrying currently
  int carrier_effort; // total effort of carriers - higher number = move faster
  int carrier_limit;
};

struct Hivemind {};

struct PartOfHivemind {
  Entity hivemind_id;
};

// Guy States
enum GuyState { SEEKING, WANDERING, CARRYING };

// Keeps the meta-information regarding a guys current state, for decision
// making purposes
struct GuyBrain {
  GuyState cur_state;
};

// struct HP {
//   int hp;
// };
