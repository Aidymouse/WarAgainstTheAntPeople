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

  FOLLOWS_MOUSE = 6,

  SCANNING_FOR = 7,
  SCANNABLE = 8,
  CARRIER = 9,
  CARRYABLE = 10,
  PERSUING = 11,

  COLLIDER = 12,
  COLLIDED = 13,

  BUILDABLE = 14,
  RESOURCE = 15,

  // GUY
  GUY_BRAIN = 16,
  GUY_WANDERING = 17,

  // Hivemind
  HV_BRAIN = 18,
  HV_PARTICIPANT = 19,

  // Traits
  HANDSFREE = 20,

  // COL_MALLET = 7,
  //
  // SCANNABLE = 8,
  // PERSUING = 9,
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
  Collision collisions[MAX_COLLISIONS_PER_ENTITY]; // You can collide with up to
                                                   // this many things per frame

  int num_collisions;
};

struct HandsFree {};

struct Collider {
  CollisionShapeType type;
  CollisionShape shape;
  Collision collision_data;
};

#define MAX_MULTI_COLLISIONS 4
struct MultiCollider {
  CollisionShapeType types[MAX_MULTI_COLLISIONS];
  CollisionShape shapes[MAX_MULTI_COLLISIONS];
  Collision collidion_datas[MAX_MULTI_COLLISIONS];
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

enum ResourceTypes { RT_SCRAP_METAL };

struct Resource {
  ResourceTypes type;
  short value;
};

#define MAX_BUILDABLE_STAGES 4
struct Buildable {
  int cur_stage;
  int num_stages;
  AnimFrame stage_frames;
  unsigned short points_required[MAX_BUILDABLE_STAGES];
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

// Guy States
enum GuyState { SEEKING, WANDERING, CARRYING };

// Keeps the meta-information regarding a guys current state, for decision
// making purposes
struct GuyBrain {
  GuyState cur_state;
  float die_timer;
};

// struct HP {
//   int hp;
// };
