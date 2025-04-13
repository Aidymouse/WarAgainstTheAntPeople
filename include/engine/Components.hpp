#pragma once

#include <SDL3/SDL.h>
#include <bitset>
#include <ecs/Entity.hpp>
#include <engine/Collisions.h>
#include <memory>
#include <optional>

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
  float z; // Used for fake 3d. Subtracted from Y to get vertical pos on screen,
           // but sorted with higher Z = higher.
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

// Can be smashed by big weights (like hammer)
struct Smashable {};

struct Visible {
  // Something like sprite
  SDL_Texture *texture;
  SDL_FRect frame;
};

struct Clickable {};

enum RESOURCE_TYPES { SCRAP_METAL };

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
};

struct Carryable {
  std::optional<Entity> carried_by;
};
