#pragma once

#include <ecs/Entity.hpp>

enum CollisionType { SQUISH, EXPLOSION, FOUND_SOUGHT };

struct c_Squish {
  // CollisionType type = CollisionType::SQUISH;
  int strength;
};

struct c_Explosion {
  // CollisionType type = CollisionType::EXPLOSION;
  int strength;
};

struct c_Found_Sought {
  // CollisionType type = CollisionType::FOUND_SOUGHT;
  Entity sought_id;
};

union CollisionData {
  c_Squish squish;
  c_Explosion explosion;
  c_Found_Sought found_sought;
};

struct Collision {
  CollisionType type;
  CollisionData data;
};
