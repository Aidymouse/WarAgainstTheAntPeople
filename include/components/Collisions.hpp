#pragma once

#include <ecs/Entity.hpp>

enum CollisionType { SQUISH, EXPLOSION, FOUND_SOUGHT, NO_OP };

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

struct c_no_op {};

union CollisionData {
  c_Squish squish;
  c_Explosion explosion;
  c_Found_Sought found_sought;

  c_no_op no_op;
};

struct Collision {
  CollisionType type;
  CollisionData data;
};
