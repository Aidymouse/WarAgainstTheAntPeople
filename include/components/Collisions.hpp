#pragma once

#include <ecs/Entity.hpp>
#include <util/Vec2.hpp>

enum CollisionType {
  SQUISH,
  EXPLOSION,

  // Guy specific
  FOUND_SOUGHT,
  GO_SOMEWHERE_ELSE, // Used to make guys walk somewhere else when bumping into
                     // something

  PICK_ME_UP,
  NO_OP
};

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

struct c_Go_Somewhere_Else {
  // CollisionType type = CollisionType::FOUND_SOUGHT;
  int pos_away_from_x;
  int pos_away_from_y;
};

struct c_Pick_Me_Up {
  Entity to_pick_up;
};

struct c_no_op {};

union CollisionData {
  c_Go_Somewhere_Else go_somewhere_else;
  c_Squish squish;
  c_Explosion explosion;
  c_Found_Sought found_sought;
  c_Pick_Me_Up pick_me_up;

  c_no_op no_op;
};

struct Collision {
  CollisionType type;
  CollisionData data;
};
